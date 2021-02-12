import yagmail
from datetime import datetime

now = datetime.now()

current_time = now.strftime("%H:%M:%S")
print("Current Time =", current_time)
user = 'huestajarck@gmail.com'
app_password = 'xnjmzfzrspcvcevp'
to = 'your_recipent@gmail.com'

subject = 'test subject 1'
content = ['mail body content']

while True:

    if datetime.now().hour == 7 or datetime.now().hour == 17:
        with yagmail.SMTP(user, app_password) as yag:
            yag.send(to, subject, content)
            print('Sent email successfully')

    # current_time = now.strftime("%H:%M:%S")
    # print("Current Time =", current_time)