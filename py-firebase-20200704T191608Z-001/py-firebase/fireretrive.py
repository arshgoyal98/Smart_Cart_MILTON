from firebase import firebase


URL='https://lowes-app.firebaseio.com'
firebase = firebase.FirebaseApplication(URL, None)
result = firebase.get('/users/jack/name', '')
print(result)