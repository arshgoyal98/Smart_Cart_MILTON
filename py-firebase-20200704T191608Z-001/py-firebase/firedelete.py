from firebase import firebase
URL='https://lowes-app.firebaseio.com'
firebase = firebase.FirebaseApplication(URL, None)
firebase.delete('/users/jack/name', '-LjLUhaWGuxNd5gOEmse')
print('Record Deleted')