import requests
from bs4 import BeautifulSoup
import time
from googletrans import Translator

def fetch_hacker_news_github_links():
    translator = Translator()
    
    page_number = 1
    while True:
        url = f'https://news.ycombinator.com/?p={page_number}'
        # print(f'Fetching page {page_number}...')

        headers = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/90.0.4430.212 Safari/537.36'
        }
        
        response = requests.get(url, headers=headers)
        soup = BeautifulSoup(response.text, 'html.parser')

        titles = soup.find_all('tr', class_='athing')
        if not titles:
            print("No more articles found. Exiting.")
            break
        
        for title in titles:
            title_line = title.find('span', class_='titleline')
            link = title_line.find('a')
            if link and 'github.com' in link.get('href'):
                translated_title = translator.translate(link.text, dest='ru').text
                print(f'Описание: {translated_title}\nСсылка: {link.get("href")}\n\n')

        # time.sleep(2) 
        page_number += 1

if __name__ == "__main__":
    fetch_hacker_news_github_links()
