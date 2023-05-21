#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "node.h"
using namespace std;
string category[11];
struct attrSplitVal
{
    int attr;
    float splitVal;
};

typedef struct attrSplitVal Struct;

float calculateInfoGain(vector<float> data, int attr, float splitVal)
{
    float entries;
    entries = data.size();
    float leftEntries;
    float rightEntries;

    vector<float> dataLeft;
    vector<float> dataRight;

    float totalCount=0;

    float fiveCount=0;
    float sixCount=0;
    float sevenCount=0;

    float fiveProb=0;
    float sixProb=0;
    float sevenProb=0;

    float fiveTerm=0;
    float sixTerm=0;
    float sevenTerm=0;

    float lessCount=0;
    float lessProb=0;
    float greatEQCount=0;
    float greatEQProb=0;

    float infoContentRoot=0;
    float infoContentLeft=0;
    float infoContentRight=0;
    float gain=0;

    for (int i=0+attr; i<entries; i+=12)
    {
        if(data.at(i)<splitVal)
        {
            dataLeft.push_back(data.at(i-attr+11));
        }
        else
        {
            dataRight.push_back(data.at(i-attr+11));
        }
        totalCount++;
    }

    leftEntries = dataLeft.size();
    rightEntries = dataRight.size();

    for (int i=11; i<entries; i+=12)
    {
        if(data.at(i)==5)
        {
            fiveCount++;
        }
        else if(data.at(i)==6)
        {
            sixCount++;
        }
        else if(data.at(i)==7)
        {
            sevenCount++;
        }
    }

    // Calculate root information content
    lessProb=leftEntries/entries;
    greatEQProb=rightEntries/entries;
    fiveProb=fiveCount/entries;
    sixProb=sixCount/entries;
    sevenProb=sevenCount/entries;
    if(fiveCount==0)
    {
        fiveTerm=0;
    }
    else
    {
        fiveTerm=-fiveProb*log2(fiveProb);
    }

    if(sixCount==0)
    {
        sixTerm=0;
    }
    else
    {
        sixTerm=-sixProb*log2(sixProb);    
    }
    
    if(sevenCount==0)
    {
        sevenTerm=0;
    }
    else
    {
        sevenTerm=-sevenProb*log2(sevenProb);    
    }
    
    
    infoContentRoot=fiveTerm+sixTerm+sevenTerm;


    // Calculate left node information content
    fiveCount=0;
    sixCount=0;
    sevenCount=0;
    totalCount=0;
    for (int i=0; i<leftEntries; i++)
    {
        if(dataLeft.at(i)==5)
        {
            fiveCount++;
        }
        else if(dataLeft.at(i)==6)
        {
            sixCount++;
        }
        else if(dataLeft.at(i)==7)
        {
            sevenCount++;
        }
        totalCount++;
    }
    fiveProb=fiveCount/leftEntries;
    sixProb=sixCount/leftEntries;
    sevenProb=sevenCount/leftEntries;


    if(fiveCount==0)
    {
        fiveTerm=0;
    }
    else
    {
        fiveTerm=-fiveProb*log2(fiveProb);
    }

    if(sixCount==0)
    {
        sixTerm=0;
    }
    else
    {
        sixTerm=-sixProb*log2(sixProb);    
    }

    if(sevenCount==0)
    {
        sevenTerm=0;
    }
    else
    {
        sevenTerm=-sevenProb*log2(sevenProb);    
    }
    infoContentLeft=fiveTerm+sixTerm+sevenTerm;

    // Calculate right node information content
    fiveCount=0;
    sixCount=0;
    sevenCount=0;
    totalCount=0;
    for (int i=0; i<rightEntries; i++)
    {
        if(dataRight.at(i)==5)
        {
            fiveCount++;
        }
        else if(dataRight.at(i)==6)
        {
            sixCount++;
        }
        else if(dataRight.at(i)==7)
        {
            sevenCount++;
        }
        totalCount++;
    }
    fiveProb=fiveCount/rightEntries;
    sixProb=sixCount/rightEntries;
    sevenProb=sevenCount/rightEntries;

    if(fiveCount==0)
    {
        fiveTerm=0;
    }
    else
    {
        fiveTerm=-fiveProb*log2(fiveProb);
    }

    if(sixCount==0)
    {
        sixTerm=0;
    }
    else
    {
        sixTerm=-sixProb*log2(sixProb);    
    }

    if(sevenCount==0)
    {
        sevenTerm=0;
    }
    else
    {
        sevenTerm=-sevenProb*log2(sevenProb);    
    }
    infoContentRight=fiveTerm+sixTerm+sevenTerm;


    // Calculate Information Gain
    gain=infoContentRoot-lessProb*infoContentLeft-greatEQProb*infoContentRight;
    return gain;
}

attrSplitVal chooseSplit(vector<float> data)
{
    attrSplitVal s;
    int bestAttr;
    float bestSplitVal;
    float bestGain=0;
    int entries;
    entries = data.size();
    int counter;
    float splitVal;
    float gain=0;
    for (int i=0; i<11; i++)
    {
        counter=0;
        vector<float> tempAttributeVector;
        vector<float> actualAttributeVector;
        for(int j=0; j<entries; j+=12)
        {
            tempAttributeVector.push_back(data.at(i+j));
        }
        sort(tempAttributeVector.begin(), tempAttributeVector.end());
        actualAttributeVector.push_back(tempAttributeVector.at(0));
        for(int j=1; j<tempAttributeVector.size(); j++)
        {
            if(tempAttributeVector.at(j)!=tempAttributeVector.at(j-1))
            {
                actualAttributeVector.push_back(tempAttributeVector.at(j));
            }
        }

        for(int j=0; j<(entries/12)-1;j++)
        {
            splitVal=0.5*(tempAttributeVector.at(j)+tempAttributeVector.at(j+1));
            gain=calculateInfoGain(data, i, splitVal);
            if(gain>bestGain)
            {
                bestGain=gain;
                bestAttr=i;
                bestSplitVal=splitVal;

            }
        }
    }
    s.attr=bestAttr;
    s.splitVal=bestSplitVal;
    return s;
}

node * DTL(vector<float> data, int minLeaf)
{
    attrSplitVal  result;
    int counter=0;
    int fiveCount=0;
    int sixCount=0;
    int sevenCount=0;
    int modeVal=0;
    int mode=0;
    vector<int> labelCountVec;

    float splitVal;
    int attrIndex;

    vector<float> qualityData;
    vector<float> leftData;
    vector<float> rightData;
    int entries;
    entries = data.size();

    // Check if yi = yj for all i,j
    bool allSameLabel=true;
    for(int i=11; i<entries-12; i+=12)
    {
        if(data.at(i)!=data.at(i+12))
        {
            allSameLabel=false;

        }
        qualityData.push_back(data.at(i));
    }
    qualityData.push_back(data.at(entries-1));

    // Checks if xi=xj for all i,j
    bool allSameAtt=true;
    for(int i=0; i<11; i++)
    {

        for(int j=0; j<entries-12; j+=12)
        {
            if(data.at(i+j)!=data.at(i+j+12))
            {
                allSameAtt=false;
                break;
            }
        }

        if(!allSameAtt)
        {
            break;
        }
    }


    if(qualityData.size()<=minLeaf || allSameLabel==true || allSameAtt==true)
    {
        // Create new leaf node n
        node * myNode=new node;
        myNode->setLeafNode(true);
        myNode->setData(qualityData,qualityData.size());
        for(int i=11; i<entries; i+=12)
        {
            if(data.at(i)==5)
            {
                fiveCount++;
            }
            else if(data.at(i)==6)
            {
                sixCount++;
            }
            else if(data.at(i)==7)
            {
                sevenCount++;
            }
        }
        // calculate whether there is a unique node.

        labelCountVec.push_back(fiveCount);
        labelCountVec.push_back(sixCount);
        labelCountVec.push_back(sevenCount);

        int actualMax=0;
        int tempMax=0;
        int tempMaxIndex=-1;

        // Logic for calculating label uniqueness
        for(int i=0; i<3; i++)
        {
            if(labelCountVec.at(i)>tempMax)
            {
                actualMax=labelCountVec.at(i);
                counter=0;
                for(int j=0; j<3; j++)
                {
                    if(labelCountVec.at(i)==labelCountVec.at(j))
                    {
                        counter++;
                    }    
                }
                if(counter<=1)
                {
                    tempMax=labelCountVec.at(i);
                    tempMaxIndex=i;
                }

            }

        }

        if(actualMax==tempMax)
        {
            if(tempMaxIndex==0)
            {
                myNode->setLabel("5");
            }
            else if(tempMaxIndex==1)
            {
                myNode->setLabel("6");
            }
            else if(tempMaxIndex==2)
            {
                myNode->setLabel("7");
            }
            else
            {
                myNode->setLabel("unknown");
            }
        }
        else
        {
            myNode->setLabel("unknown");
        }
        return myNode;
    }

    // chooseSplit(data) --> Algorithm 2
    result = chooseSplit(data);

    attrIndex=result.attr;
    splitVal=result.splitVal;
    node * myNode=new node;
    myNode->setData(qualityData,qualityData.size());
    myNode->setSplitVal(splitVal);
    myNode->setSplitValAttr(attrIndex);
  
    node * leftNode=new node;
    node * rightNode=new node;



    //SPLIT DATA

    for(int i=attrIndex; i<entries; i+=12)
    {
        if(data.at(i)<=splitVal)
        {
            for(int j=i-attrIndex; j<i+12-attrIndex ; j++)
            {
                leftData.push_back(data.at(j));
            }            
        }
        else
        {
            for(int j=i-attrIndex; j<i+12-attrIndex; j++)
            {
                rightData.push_back(data.at(j));
            }
            
        }
    }

    leftNode=DTL(leftData,minLeaf);
    rightNode=DTL(rightData,minLeaf);
    myNode->myLeftNode=leftNode;
    myNode->myRightNode=rightNode;

    return myNode;
}

string predict_DTL(node * myNode, vector<float> data)
{

    int attrIndex;
    float splitVal;

    while(myNode->getLeafNode()==false)
    {
        
        attrIndex=myNode->getSplitValAttr();
        splitVal=myNode->getSplitVal();
        if(data.at(attrIndex)<=splitVal)
        {
            myNode=myNode->myLeftNode;
        }
        else
        {
            myNode=myNode->myRightNode;
        }
    }
    return myNode->getLabel();
}

int main(int argc, char **argv)
{
    string input1=argv[1];
    string input2=argv[2];
    string input3=argv[3];

    ifstream inFile;
    string tempInput;
    float tempFloat;
    vector<string> stringData;
    vector<float> data;
    bool input=true;
    int  minLeaf=stoi(input3);
    node * root = new node;
    node * tempNode= new node;
    string tempString;
    vector<string> testAttrString;
    vector<float> testAttrData;
    
    vector<string> output;
    int final;
    inFile.open(input1);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1);
    }
    

    while(input)
    {
        inFile >> tempInput;
        if(!inFile)
        {
            input=false;
            break;
        }
        stringData.push_back(tempInput);
    }
    
    inFile.close();
    for(int i=0; i<11; i++)
    {
        category[i]=stringData.at(i);
    }
    for(int i=12; i<stringData.size(); i++)
    {
        tempFloat=stof(stringData.at(i));
        data.push_back(tempFloat);
    }



    input=true;
    tempInput="";
    inFile.open(input2);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1);
    }
    while(input)
    {
        inFile >> tempInput;
        if(!inFile)
        {
            input=false;
            break;
        }
        testAttrString.push_back(tempInput);
    }
    inFile.close();
    for(int i=11; i<testAttrString.size(); i++)
    {
        tempFloat=stof(testAttrString.at(i));
        testAttrData.push_back(tempFloat);

    }
    
    root=DTL(data,minLeaf);
    for(int i=0; i<testAttrData.size()/11; i++)
    {
        vector<float> testAttrDataTemp;
        for(int j=0; j<11; j++)
        {
            tempFloat=testAttrData.at(j+11*i);
            testAttrDataTemp.push_back(tempFloat);
        }
        output.push_back(predict_DTL(root, testAttrDataTemp));
    }
    for(int i=0; i<(testAttrData.size()/11); i++)
    {
        cout<<output.at(i)<<endl;
    }
    return 0;
}