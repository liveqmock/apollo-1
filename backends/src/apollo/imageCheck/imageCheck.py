#! /usr/bin/python
#-*-coding:utf-8-*- 
import os
import sys
import numpy as np
import cv2
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
from common.utils.scanFile import ProgressStatistics
from apollo.commHandler import parameters   
checkPath = str(parameters['path'])

Const_Image_Format = [".jpg",".jpeg",".bmp",".png"]
class ImageCheck(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        self. currentFileNum=0       
        self.resultDict={}
        self.resultList=[]
        pass 
            
    
    def match(self,checkPathPara):
        img_rgb = cv2.imread('t1.png')
        img_gray = cv2.cvtColor(img_rgb, cv2.COLOR_BGR2GRAY)
        template = cv2.imread(checkPathPara,0) 
        w, h = template.shape[::-1]
        res = cv2.matchTemplate(img_gray,template,cv2.TM_CCOEFF_NORMED)
        # print res
        threshold = 0.5
        loc = np.where( res >= threshold)
#         print loc 
#         print len(loc[0])
        locLen=len(loc[0])
        if locLen:
            return 1
        else:
            return 0
        
    def walkdir(self,dirName,fileTotalNumPara):  
        ls = os.listdir(dirName)
        for fn in ls:             
            self.currentFileNum=self.currentFileNum+1 
            temp = os.path.join(dirName, fn) 
            if(os.path.isdir(temp)):  
                print(temp)
                prors = ps.getProgressStatisticsInfo(fileTotalNumPara, self.currentFileNum )                       
                progReportMsg=objectTemp.orgProgReportMsg(prors, temp)
                objectTemp.sendMsgToUI(progReportMsg)  
                self.walkdir(temp,fileTotalNumPara)  
            else:                  
                print(temp)
                newDir=temp
                if os.path.isfile(newDir):
                    if newDir and(os.path.splitext(newDir)[1] in Const_Image_Format):
                        if self.match(newDir):
    #                         currentFileNum=currentFileNum+1
                            self.resultDict['found']=temp
                            self.resultList.append(self.resultDict)
                            dataReportMsg=objectTemp.orgDataReportMsg(self.resultList)
                            objectTemp.sendMsgToUI(dataReportMsg) 
                            self.resultDict={}
                            self.resultList=[]
                prors = ps.getProgressStatisticsInfo(fileTotalNumPara, self.currentFileNum )                       
                progReportMsg=objectTemp.orgProgReportMsg(prors, temp)
                objectTemp.sendMsgToUI(progReportMsg) 
                    
         
if __name__ == "__main__":  
    objectTemp=ImageCheck()  
    try:        
        ps = ProgressStatistics() 
        fileTotalNum=ps.filenum(checkPath)
        objectTemp.walkdir(checkPath,fileTotalNum)
                            
        progReportMsg=objectTemp.orgProgReportMsg("100", "图片信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("图片信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("图片信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)  
