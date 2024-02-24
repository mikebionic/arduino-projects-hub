def get_text():
	f=open("news_latest.txt", "r")
	if f.mode == 'r':
		contents =f.read()
		contents_list = contents.split(', ')
		# print (contents_list)
		return (contents_list)
