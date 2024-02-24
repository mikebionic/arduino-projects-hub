from flask import Flask, flash, request, redirect, render_template, url_for
from flask_sqlalchemy import SQLAlchemy

from bs4 import BeautifulSoup
import requests

app = Flask(__name__)
app.config['SECRET_KEY'] = 'zTctP8FjbAAmy4?NuM3u'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///mirror.db'
db = SQLAlchemy(app)


class Weather(db.Model):
	id = db.Column('id', db.Integer, nullable= False, primary_key=True)
	state = db.Column('state', db.String, nullable = False)
	def __repr__(self):
		return "Weather({},{})".format(self.id,self.state)


weather_url = "https://rp5.ru/Погода_в_Ашхабаде,_Кеши"
weather_res = requests.get(weather_url)
weather_res.raise_for_status()
weather_soup = BeautifulSoup(weather_res.text,'html.parser')
meta_tags = weather_soup.find_all('meta')
to_check = meta_tags[1]
weather = str (to_check)
weather_splitted = weather[15:-30]

try:
    latest_weather = Weather(state=weather_splitted)
    db.session.add(latest_weather)
    db.session.commit()
except ValueError as ex:
    print("Exception caught:", ex)

