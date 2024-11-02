import requests
from bs4 import BeautifulSoup

# URL сайта, который мы будем парсить
url = 'https://forklog.com/news'

try:
    # Выполняем GET-запрос к сайту
    response = requests.get(url)
    response.raise_for_status()  # Проверяем, успешен ли запрос (вызывает исключение для ошибок)

    # Создаем объект BeautifulSoup для парсинга HTML
    soup = BeautifulSoup(response.text, 'html.parser')

    # Находим блоки новостей, используя класс 'post_item'
    articles = soup.find_all('div', class_='post_item')

    if not articles:
        print("Новости не найдены на странице.")
    else:
        # Проходим по всем найденным новостям и извлекаем информацию
        for article in articles:
            # Ищем заголовок и ссылку
            title_tag = article.find('a')
            if title_tag:
                title = title_tag.find('p').get_text(strip=True)  # Заголовок
                link = title_tag['href']
                
                # Проверяем, если ссылка относительная, добавляем базовый URL
                if not link.startswith('http'):
                    link = 'https://forklog.com' + link
                
                # Ищем краткое содержание
                summary_tag = article.find('span', class_='post_excerpt')
                summary = summary_tag.get_text(strip=True) if summary_tag else 'Краткое содержание отсутствует.'

                # Ищем автора
                author_tag = article.find('a', class_='author_lnk')
                author = author_tag.get_text(strip=True) if author_tag else 'Автор не указан'

                # Ищем дату публикации
                date_tag = article.find('span', class_='post_date')
                date = date_tag.get_text(strip=True) if date_tag else 'Дата не указана'

                # Ищем количество просмотров
                views_tag = article.find('span', class_='single_post_views')
                views = views_tag.get_text(strip=True) if views_tag else 'Просмотры не указаны'

                print(f'Заголовок: {title}\nКраткое содержание: {summary}\nСсылка: {link}\nАвтор: {author}\nДата: {date}\nПросмотры: {views}\n')

except requests.exceptions.HTTPError as http_err:
    print(f'HTTP ошибка: {http_err}')
except requests.exceptions.RequestException as req_err:
    print(f'Ошибка запроса: {req_err}')
except Exception as e:
    print(f'Произошла ошибка: {e}')
