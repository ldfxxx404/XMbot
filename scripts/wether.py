import requests
import sys
import os

def fetch_geocode(city):
    url = f"https://nominatim.openstreetmap.org/search?q={city}&format=json&addressdetails=1"
    headers = {
        "User-Agent": "WeatherApp/1.0 (your-email@example.com)"  # Update this
    }
    response = requests.get(url, headers=headers)
    response.raise_for_status()
    return response.json()

def fetch_weather_data(lat, lon):
    url = f"https://api.open-meteo.com/v1/forecast?latitude={lat}&longitude={lon}&current_weather=true"
    response = requests.get(url)
    response.raise_for_status()
    return response.json()

def format_location(geocode_response):
    display_name = geocode_response[0].get("display_name", "Unknown location")
    return f"Location: {display_name}"

def format_weather_data(weather_response):
    current = weather_response.get("current_weather", {})
    temp = current.get("temperature", 0.0)
    wind_speed = current.get("windspeed", 0.0)
    precip_prob = current.get("precipitation", 0.0)

    return (
        f"Current temperature: {temp}°C\n"
        f"Wind speed: {wind_speed} m/s\n"
        f"Precipitation probability: {precip_prob}%"
    )

def main():
    if len(sys.argv) != 3:
        print("Usage: python weather.py <input_file> <output_file>")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    try:
        # Read the city name from the input file
        with open(input_file, 'r') as file:
            city = file.readline().strip()

        # Fetch geocode data
        geocode_response = fetch_geocode(city)
        if not geocode_response:
            output = "City not found."
        else:
            location_info = format_location(geocode_response)
            latitude, longitude = geocode_response[0]["lat"], geocode_response[0]["lon"]

            # Fetch weather data
            weather_response = fetch_weather_data(latitude, longitude)
            weather_info = format_weather_data(weather_response)

            # Prepare the output
            output = f"{location_info}\n{weather_info}"

        # Ensure the directory for the output file exists, create if necessary
        output_dir = os.path.dirname(output_file)
        if output_dir and not os.path.exists(output_dir):
            os.makedirs(output_dir)

        # Write output to the specified output file (creating it if it doesn't exist)
        with open(output_file, 'w') as file:
            file.write(output)

    except requests.RequestException as e:
        with open(output_file, 'w') as file:
            file.write(f"Error retrieving data: {e}")
        sys.exit(1)
    except FileNotFoundError:
        print(f"Error: File '{input_file}' not found.")
        sys.exit(1)

if __name__ == "__main__":
    main()
