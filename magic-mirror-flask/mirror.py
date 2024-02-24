from flask import Flask, flash, request, redirect, render_template, url_for
from flask_sqlalchemy import SQLAlchemy
import os
from datetime import datetime

app = Flask(__name__)
app.config['SECRET_KEY'] = 'zTctP8FjbAAmy4?NuM3u'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///mirror.db'
db = SQLAlchemy(app)

class Weather(db.Model):
	id = db.Column('id', db.Integer, nullable= False, primary_key=True)
	state = db.Column('state', db.String, nullable = False)
	def __repr__(self):
		return "Weather({},{})".format(self.id,self.state)

class News(db.Model):
	id = db.Column('id', db.Integer, nullable = False, primary_key=True)
	news = db.Column('news', db.String, nullable = False)
	def __repr__(self):
		return "News({},{})".format(self.id,self.news)

class Todo(db.Model):
	id = db.Column('id', db.Integer, nullable = False, primary_key=True)
	task = db.Column('task', db.String, nullable = False)
	date = db.Column(db.DateTime, nullable = False, default=datetime.utcnow)
	on_date = db.Column(db.String, nullable = False)
	def __repr__(self):
		return "News({},{},{},{})".format(self.id,self.task,self.date,self.on_date)

def check_daytime():
	now = datetime.now()
	dt_string = now.strftime("%d/%m/%Y %H:%M:%S")
	hour = now.strftime("%H")
	if int(hour)>=8 and int(hour)<=19:
		day_state="day"
	else:
		day_state="night"
	return day_state
@app.route('/to_do', methods=['GET', 'POST'])
def to_do():
	tasks = Todo.query.all()
	now = datetime.now()
	yy = now.strftime("%Y")
	mm = now.strftime("%m")
	dd = now.strftime("%d")
	templateData = {
	'this_year' : yy,
	'this_month' : mm,
	'this_day' : dd
	}
	return render_template('task_layout.html', tasks=tasks, **templateData)

@app.route('/add', methods=['POST'])
def add():
	if request.form:
		day = request.form["day"]
		month = request.form["month"]
		year = request.form["year"]
		task = request.form["task"]
		try:
			on_date = day+"/"+month+"/"+year
			new_task = Todo(task=task, on_date=on_date)
			db.session.add(new_task)
			db.session.commit()
		except ValueError as ex:
			print ("exception",ex)
	return redirect('to_do')

@app.route('/delete', methods=['POST'])
def delete():
	task_id = request.form.get("task_id")
	todo = Todo.query.filter_by(id=task_id).first()
	db.session.delete(todo)
	db.session.commit()
	return redirect('to_do')

@app.route('/', methods=['GET'])
def mirror():
	now = datetime.now()
	today = now.strftime("%d/%m/%Y")
	email = "bionicsfamily@gmail.com"
	day_state = check_daytime()
	if day_state == "day":
		weather_pic = "cloudy.jpg"
	else:
		weather_pic = "night.jpg"
	latest_weather=[]
	latest_news=[]
	weathers = Weather.query.all()
	updates = News.query.all()

	for weather in weathers:
		latest_weather.append(weather.state)

	for update in updates:
		latest_news.append(update.news)
	latest_weather = str(latest_weather[-1])
	latest_news = str(latest_news[-1])
	contents_list = latest_news.split(', ')
	task_today = Todo.query.filter_by(on_date=today).all()
	temp = "22"
	humi = "43"

	templateData = {
	'temperature' : temp,
	'humidity' : humi,
	'date_today' : today,
	'task_today' : task_today
	}
	return render_template('mirror.html', news=contents_list, 
							email=email, weather=latest_weather, 
							weather_pic=weather_pic, **templateData)


if __name__ == "__main__":
	app.run(host="0.0.0.0" , port=5000 , debug=True)

	
