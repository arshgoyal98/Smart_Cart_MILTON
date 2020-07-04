from firebase import firebase

URL='https://lowes-app.firebaseio.com'
firebase = firebase.FirebaseApplication(URL, None)
data =  { 'Name': 'John Doe',
          'MobileNo': 9876543210,
          'CustomerID': 'AD1'
          }
result = firebase.post('/users/jack/name',data)
print(result)