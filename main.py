import requests
from bs4 import BeautifulSoup

def fetch_opennet_news():
    url = "https://www.opennet.ru/opennews/index.shtml"
    response = requests.get(url)
    response.raise_for_status()  # Проверяем успешность запроса
    
    soup = BeautifulSoup(response.content, 'html.parser')
    articles = []

    # Находим все блоки новостей на странице
    news_blocks = soup.find_all('td', class_='tdate')
    
    for date_block in news_blocks:
        date = date_block.get_text(strip=True)  # Дата публикации
        
        # Находим блок с заголовком и ссылкой
        title_block = date_block.find_next('a', class_='title2')
        title = title_block.get_text(strip=True)
        link = "https://www.opennet.ru" + title_block['href']
        
        # Находим краткое описание новости
        summary_block = date_block.find_next('td', class_='chtext2')
        summary = summary_block.get_text(strip=True).split('...')[0] + '...' if summary_block else 'Описание отсутствует.'

        # Находим количество обсуждений
        discussion_block = summary_block.find('span', class_='cnt') if summary_block else None
        discussions = discussion_block.get_text(strip=True) if discussion_block else "Нет данных"

        articles.append({
            "date": date,
            "title": title,
            "summary": summary,
            "link": link,
            "discussions": discussions
        })

    return articles

def display_articles(articles):
    for article in articles:
        print(f"**{article['title']}**\n"
              f"Дата: {article['date']}\n"
              f"Описание: {article['summary']}\n"
              f"[Читать далее]({article['link']}) | Обсуждение ({article['discussions']})\n")

if __name__ == "__main__":
    news_articles = fetch_opennet_news()
    if news_articles:
        display_articles(news_articles)
    else:
        print("Новости не найдены.")
