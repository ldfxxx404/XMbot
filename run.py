import sys
import requests
import json
import os
from dotenv import load_dotenv

# Загружаем переменные окружения из .env файла
load_dotenv()

def chat_with_llama(user_input):
    url = os.getenv("LLAMA_API_URL", "http://localhost:3000/api/chat/completions") 
    api_key = os.getenv("LLAMA_API_KEY")
    model_name = os.getenv("LLAMA_MODEL_NAME", "llama3.1")  
    if not api_key:
        print("Ошибка: API-ключ не указан. Установите переменную окружения 'LLAMA_API_KEY'.")
        return

    headers = {
        "Authorization": f"Bearer {api_key}",
        "Content-Type": "application/json"
    }

    messages = [
        {"role": "user", "content": user_input}
    ]

    payload = {
        "model": model_name,
        "messages": messages
    }

    try:
        # Отправляем POST-запрос
        response = requests.post(url, headers=headers, json=payload)

        # Проверяем статус ответа
        if response.status_code == 200:
            response_data = response.json()  # Пытаемся разобрать JSON
            # Извлекаем контент ответа
            assistant_message = response_data["choices"][0]["message"].get("content", "").strip()
            print(assistant_message)
        else:
            print(f"Ошибка: {response.status_code} - {response.text}")
    except json.JSONDecodeError as e:
        print(f"Ошибка разбора JSON: {str(e)}")
        print("Полученный ответ не является корректным JSON:", response.text)
    except Exception as e:
        print(f"Произошла ошибка: {str(e)}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Использование: python app.py <запрос от пользователя>")
    else:
        user_query = " ".join(sys.argv[1:])
        chat_with_llama(user_query)
