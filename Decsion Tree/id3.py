#!/usr/bin/env python
import operator
from math import log
import fileinput




def Parse_File():
    Input = []
    Training = []
    Feature = []
    label = []
    
    # Getting input file into the 2D list
    for line in fileinput.input():
        Input.append(line.split())

    num_of_Feature = int(Input[0][0])
    
    for i in range(1, num_of_Feature+1):
        Feature.append(Input[i])

    
    for i in range (0, len(Feature)):
        label.append(Feature[i][0])
            

    for i in range(num_of_Feature+2, len(Input)):
        Training.append(Input[i])



    return Training,label


def print_list(x):
    for word in x:
        print(word)

def test_parse():
    print "Input Data:"
    print_list(Input)
    print "Features:"
    print_list(Feature)
    print "Training Data:"
    print_list(Training)


def Get_Data():
    dataSet, Feature_Title = Parse_File()

    return dataSet, Feature_Title




def Calculate_Ent(dataSet):
    num_of_Entries = len(dataSet)
    labelCounts = {}
    for Feature_Vector in dataSet:
        currentLabel = Feature_Vector[-1]
        if currentLabel not in labelCounts:
            labelCounts[currentLabel] = 0
        labelCounts[currentLabel] += 1
    S_Ent = 0.0
    for key in labelCounts:
        prob = float(labelCounts[key])/num_of_Entries
        S_Ent -= prob * log(prob, 2)
    return S_Ent

    
def Best_Info_Gain(dataSet):
    numFeatures = len(dataSet[0]) - 1
    Total_Entropy = Calculate_Ent(dataSet)
    bestInfoGain = 0.0
    Target_Feature = -1

    for i in range(numFeatures):
        featList = [example[i] for example in dataSet]
        Vals = set(featList)
        newEntropy = 0.0
        
        for value in Vals:
            subDataSet = Split_Data(dataSet, i, value)
            prob = len(subDataSet) / float(len(dataSet))
            newEntropy += prob * Calculate_Ent(subDataSet)
        infoGain = Total_Entropy -newEntropy
        
        if infoGain > bestInfoGain:
            bestInfoGain = infoGain
            Target_Feature = i
    
    return Target_Feature

def Split_Data(dataSet, axis, value):
    retDataSet = []
    for featVec in dataSet:
        if featVec[axis] == value:
            reducedFeatVec = featVec[:axis]
            reducedFeatVec.extend(featVec[axis+1:])
            retDataSet.append(reducedFeatVec)
    return retDataSet            

def Majority_Count(classList):
    classCount = {}

    for vote in classList:
    
        if vote not in classCount.keys():
            classCount[vote] = 0
        classCount[vote] += 1
    
    return max(classCount)         
    
def createTree(dataSet, Feature_Title):
    classList = [example[-1] for example in dataSet]

    if classList.count(classList[0]) ==len(classList):
        return classList[0]
    
    if len(dataSet[0]) == 1:
        return Majority_Count(classList)
    
    bestFeat = Best_Info_Gain(dataSet)
    bestFeatLabel = Feature_Title[bestFeat]
    myTree = {bestFeatLabel:{}}
    del(Feature_Title[bestFeat])
    featValues = [example[bestFeat] for example in dataSet]
    Vals = set(featValues)
    
    for value in Vals:
        subFeature_Title = Feature_Title[:]
        myTree[bestFeatLabel][value] = createTree(Split_Data(dataSet, 
                                        bestFeat, value),subFeature_Title)
    return myTree


def print_result(d, indent=0):
    for key, value in d.iteritems():
        #if str(key) in label_tmp:
        print str(key), '='
        #else: 
            #print str(key), ':'

            
        if isinstance(value, dict):
            print_result(value, indent+1)
        else:
            print "  " + str(value)



def main():
    data,label = Get_Data()

    myTree = createTree(data,label)


    print "\n*** Assignment not finished. *** \nDescription: \nThe Tree work good. \nbut I am stuck that how can I print the nested layer of dictionary tree well. \nI have tried my best \nbut still can not print it nice, but the algorithm works well."
    
    print "\n\n here is the tree in nested layers of dictionary \n\n"

    print myTree



main()