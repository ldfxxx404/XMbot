import requests
from googletrans import Translator

def get_joke():
    try:
        # Запрашиваем анекдот из JokeAPI
        joke_response = requests.get("https://v2.jokeapi.dev/joke/Any")
        joke_data = joke_response.json()
        
        # Обрабатываем разные типы анекдотов
        if joke_data["type"] == "single":
            joke = joke_data["joke"]
        elif joke_data["type"] == "twopart":
            joke = f"{joke_data['setup']} ... {joke_data['delivery']}"
        else:
            joke = "Не удалось получить анекдот."
        
        # Переводим анекдот на русский
        translated_joke = translate_to_russian(joke)
        
        # Выводим анекдот на английском и его перевод
        print(f"Joke in English: {joke}")
        print(f"Анекдот на русском: {translated_joke}")

    except Exception as e:
        print("Ошибка при получении анекдота: " + str(e))

def translate_to_russian(text):
    try:
        translator = Translator()
        translation = translator.translate(text, src='en', dest='ru')
        return translation.text
    except Exception as e:
        return "Ошибка при переводе анекдота: " + str(e)

# Пример вызова функции
get_joke()
