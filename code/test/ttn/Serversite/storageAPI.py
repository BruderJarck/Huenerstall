import requests
# url = "https://integrations.thethingsnetwork.org/ttn-eu/api/v2/down/huehnerstall71263/tempsens71263?key=ttn-account-v2.6p1nkE0mLVt8YrtlAwJaWZixMQgHmc3jwdBd4ozDulw"

url = 'https://tempsens71263.data.thethingsnetwork.org/api/v2/query/huehnerstall71263?Authorization: key ttn-account-v2.6p1nkE0mLVt8YrtlAwJaWZixMQgHmc3jwdBd4ozDulw'
ttnReq = requests.get(url, headers={'Authorization': 'TOK: ttn-account-v2.6p1nkE0mLVt8YrtlAwJaWZixMQgHmc3jwdBd4ozDulw'})
print(ttnReq)
#