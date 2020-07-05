import requests
URL='https://www.lowes.com/mylowes/lists'
list=requests.get(URL).json()
print(list)