#! /usr/local/bin/python

#author: guder
#date: 06.09.2013
#This is a small parser for the log_file of PQi to determine the network-bandwidth
#The network-bandwidth is returned in 10^9 Bit per seconds
#Finally the Data is written to a CSV File with the following information: rid, runtime, data_size, bandwidth - separation of coulumns with "," and lines with ";"

#Note: used data = data_len*8bytes*2 + data_len*4Bytes + 3*4Bytes + 2*4Bytes  with data_len=RIDObject.size
import os,glob
class RIDObject(object):
	def __init__(self, rid, starttime, endtime, runtime, size, data=0, bandwidth=0):
		self.RID = rid
		self.Starttime = starttime
		self.Endtime = endtime
		self.Runtime = runtime 
		self.Size = size
		self.Data = data
		self.Bandwidth = bandwidth
	def getRID(self):
		return self.RID
	def getStarttime(self):
		return self.Starttime
	def getEndtime(self):
		return self.Endtime
	def getRuntime(self):
		return self.Runtime
	def getSize(self):
		return self.Size
	def getBandwidth(self):
		return self.Bandwidth
	def getData(self):
		return self.Data
	def setStarttime(self, starttime):
		self.Starttime = starttime
	def setEndtime(self, endtime):
		self.Endtime = endtime
#	def addRuntime(self,time):
#		self.Runtime += time
	def addSize(self, size):
		self.Size += (size+12+8)
	def calculateData(self):
		self.Data = self.Size*(8*2+4)
	def calculateBandwidth(self):
		runtime = self.Endtime - self.Starttime
		self.Runtime = runtime
		self.Bandwidth = (self.Data/runtime)*8/1000000
	def echo(self):
		print "RID: " + str(self.RID)
		print "Runtime: " + str(self.Runtime)
		print "Size: " + str(self.Size)
		print "Bandwidth: " + str(self.Bandwidth) + "\n"
		


def contains(list, filter):
    for x in list:
        if filter(x):
            return True
    return False
tmpFile = open("log_temp.txt", "w")

for filename in glob.glob("log_file_*"):
        print filename
        #copying log_file of client into log_file of server
        clientFile = open(filename, "r")
        for line in clientFile:
                tmpFile.write(line)
        clientFile.close()
tmpFile.close()
	
print "Start parsing-session"
 
currentObject = None
objectList = []
starttime = 0
endtime = 0
inputFile = "log_temp.txt"
file = open(inputFile, "r")



#implementation of parsing
for line in file:
	#aufsplitten der Zeile in name-value pairs
	split1 = line.split("#")
	for element in split1:
		#aufsplitten von name-value 
		split2 = element.split(":")
		if(split2[0] == "rid"):
			if contains(objectList, lambda x: x.RID == split2[1]):
				Object = [x for x in objectList if x.RID == split2[1]]
				currentObject = Object[0]
				#print "Element war in Liste enthalten"
			else:
				objectList.append(RIDObject(split2[1],0,0,0,0))
				currentObject=objectList[len(objectList)-1]
				#print "Liste war leer"
		elif(split2[0] == "start_time"):
			#starttime doesn't exist yet
			if(currentObject.getStarttime() == 0):
				currentObject.setStarttime(float(split2[1]))
			#current starttime smaller than existing: overwrite
			elif(float(split2[1]) <= currentObject.getStarttime()):
				currentObject.setStarttime(float(split2[1]))

			#current starttime greater than existing: doing nothing

		elif(split2[0] == "end_time"):
			#endtime doesn't exist yet
			if(currentObject.getEndtime() == 0):
				currentObject.setEndtime(float(split2[1]))
			#current endtime is greater than existing: overwrite
			elif(float(split2[1]) >= currentObject.getEndtime()):
				currentObject.setEndtime(float(split2[1]))

			#current endtime is smaller than existing: doing nothing

		elif(split2[0] == "size"):
			currentObject.addSize(int(split2[1]))

print "Parsing-session succesfull"
			
#sort list (key=RID)
objectList.sort(key=lambda x: x.RID)		
			
#calculate bandwidth
for element in objectList:
	element.calculateData()
	element.calculateBandwidth()
			
#output to CSV file (it is possible to do that directly in the loop which calculates the bandwidth)
outputFile = open("cluster_network_bandwidth.csv", "w+")
outputFile.write("rid, runtime, starttime, endtime, data, bandwidth;\n")
for element in objectList:
	outputFile.write( str(element.getRID()) + ", " + str(element.getRuntime()) + ", "+ str(element.getStarttime()) +", " + str(element.getEndtime())+ ", " + str(element.getData()) + ", " + str(element.getBandwidth()) + ";\n" )
			
#simple output for testing
def printAll(objectList):
	for element in objectList:
		element.echo()
		
#	printAll(objectList)

