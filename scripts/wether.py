import requests
import sys

def fetch_geocode(city):
    url = f"https://nominatim.openstreetmap.org/search?q={city}&format=json&addressdetails=1"
    headers = {
        "User-Agent": "WeatherApp/1.0 (your-email@example.com)"  # Replace with your email or app info
    }
    response = requests.get(url, headers=headers)
    response.raise_for_status()  # Raises an error if the request fails
    return response.json()

def fetch_weather_data(lat, lon):
    url = f"https://api.open-meteo.com/v1/forecast?latitude={lat}&longitude={lon}&current_weather=true"
    response = requests.get(url)
    response.raise_for_status()
    return response.json()

def print_location(geocode_response):
    display_name = geocode_response[0].get("display_name", "Unknown location")
    print(f"Location: {display_name}")

def print_weather_data(weather_response):
    current = weather_response.get("current_weather", {})
    temp = current.get("temperature", 0.0)
    wind_speed = current.get("windspeed", 0.0)
    precip_prob = current.get("precipitation", 0.0)

    print(f"Current temperature: {temp}°C")
    print(f"Wind speed: {wind_speed} m/s")
    print(f"Precipitation probability: {precip_prob}%")

def main():
    if len(sys.argv) != 2:
        print("Usage: python weather.py <city_name>")
        sys.exit(1)

    city = sys.argv[1]

    try:
        geocode_response = fetch_geocode(city)
        if not geocode_response:
            print("City not found.")
            sys.exit(1)

        print_location(geocode_response)
        latitude, longitude = geocode_response[0]["lat"], geocode_response[0]["lon"]

        weather_response = fetch_weather_data(latitude, longitude)
        print_weather_data(weather_response)

    except requests.RequestException as e:
        print(f"Error retrieving data: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
