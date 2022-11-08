import jsonCreater as jc

dict = {"name": "John", "age": 30, "city": "New York"}
print(jc.createJson(dict))
jc.saveJson(dict)
