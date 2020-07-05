## Used for fetching data from user Dashboard on Lowe's website. */

import requests
URL='https://www.lowes.com/mylowes/lists'  #Corresponds to the actuaL URL on Lowe's Dshboard.
list=requests.get(URL).json() #Fetching the data as a Json object
print(list) 
