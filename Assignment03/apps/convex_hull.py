import csv
import random 
def linetest(x: tuple, y:tuple,z:tuple ):
    a = y[1] - x[1]
    b = x[0] - y[0]
    c = x[0]*y[1] - y[0]*x[1]

    return -(a * z[0] + b * z[1] - c)

def makeCoords(number:int):
    with open("RandomPoints.csv","w", newline='') as csvfile:
        file_writer = csv.writer(csvfile, quoting = csv.QUOTE_NONNUMERIC)
        for x in range(number):
            #generate two random numbers in range
            a = random.randrange(1,1000)
            b = random.randrange(1,1000)
            #print to csv
            file_writer.writerow([a,b])         
    csvfile.close()

def readCoords(fileName:str) ->list:
    outList = []
    with open(fileName,"r") as csvfile:
        fileReader = csv.reader(csvfile, quoting = csv.QUOTE_NONNUMERIC)
        for row in fileReader:
            outList = outList + [tuple(row)]
    csvfile.close()
    return outList


#Problem 3
def convexHull(points:list)->list:
    #Flags for above/below
    above = False
    below = False
    outList = []
    for point in points:
        for current in points[points.index(point)::]:
            for next in points:
                if point != current and point != next:
                    #Set flags
                    if linetest(point,current, next) > 0:
                        above = True
                    elif linetest(point,current, next) < 0:
                        below = True

                    #if both set, no need to continue
                    if above and below:
                        break

            #If neither flags were set, log the coordinates
            if above != below:
                if point not in outList:
                    outList.append(point)
                    #outList = outList + [point]
                if current not in outList:
                    #outList = outList + [current]
                    outList.append(current)

            #Reset flags for next set of points
            above = False
            below = False
            
    return outList
 
if __name__ == "__main__":
    while True:
        try:
            makeCoords(int(input("Enter the number of points to create: ")))
            break
        except ValueError:
            print("ERROR: Enter a number when prompted.")
    out = readCoords("RandomPoints.csv")
    convex_hull_list = convexHull(out)

    #Output to a txt file
    file = open("Convex Hull.txt", "w")
    print("\nConvex Hull for Points in RandomPoints.csv:")
    file.write("Convex Hull for Points in RandomPoints.csv:\n")

    #Print each point
    for point in convex_hull_list:
        print (point)
        file.write(str(point) + "\n")
    file.close()