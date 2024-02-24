from bs4 import BeautifulSoup
import requests

weather_url = "https://rp5.ru/Погода_в_Ашхабаде,_Кеши"

weather_res = requests.get(weather_url)

weather_res.raise_for_status()
weather_soup = BeautifulSoup(weather_res.text,'html.parser')

meta_tags = weather_soup.find_all('meta')
to_check = meta_tags[1]
weather = str (to_check)

print(weather[15:-30])
