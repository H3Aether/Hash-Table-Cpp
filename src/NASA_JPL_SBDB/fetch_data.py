###########################################################################
##### GET DATA FROM "NASA JPL SBDB QUERY API" AND SAVE IT TO CSV FILE #####
###########################################################################

# Using NASA/JPL Small-Body Database Query API to fetch data
# https://ssd-api.jpl.nasa.gov/doc/sbdb_query.html

from venv import create
import requests
import json

uri = "https://ssd-api.jpl.nasa.gov/sbdb_query.api"

def createJSON():
    # Fetch data from API
    response = requests.get(uri, params={"fields": "spkid,full_name,kind,pdes,name,moid,diameter,GM,density,albedo"})
    data = response.json()
    
    # Write data to file
    return data

def JSONtoCSV(data, csv_filename):
    # Write data to file
    with open(csv_filename, "w") as file:
        fields_number = len(data["fields"])
        for body in data["data"]:
            for i in range(fields_number):
                if i == 1: # full_name always starts with 5 spaces. Remove them
                    file.write(str(body[i][5:]))
                else:
                    if body[i] is None:
                        file.write("0")
                    else:
                        file.write(str(body[i]))
                if i != fields_number - 1:
                    file.write(",")
            file.write("\n")

def main():
    csv_filename = "./NASA_JPL_SBDB/data.csv"
    data = createJSON()
    number_of_bodies = len(data["data"])
    JSONtoCSV(data, csv_filename)
    print("Done! " + str(number_of_bodies) + " bodies saved to " + csv_filename)
    return

if __name__  == "__main__":
    main()