import numpy as np
import cv2
import math
#capture webcam video
cap = cv2.VideoCapture(0)
width, height = 1920,1080
cap.set(3,width)
cap.set(4,height)

#create a method that can seperate the foreground from the background
fgbg = cv2.createBackgroundSubtractorMOG2()

#setup outfile for writing video
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('/home/sm/Desktop/keyboard.avi',fourcc, 20.0, (1280,960))

#define alphabet position
position = 0
#define hand position
hand_position = 0,0
hand_on_keyboard = False
letter_selected = False
#define font and text color
font = cv2.FONT_HERSHEY_SIMPLEX
color = (13,32,210)

#create a list for the word
word = ''

#create a letter buffer
letter_buffer = []

#define frame_num
frame_num = 0

#function that determines distance between two points
def distance(p0,p1):
    return math.sqrt((p1[1]-p0[1])**2+(p1[0]-p0[0])**2)

#main loop
while True:

    #read a frame from the webcam
    _, frame = cap.read()
    frame = cv2.flip(frame, 1)
    frame_num += 1

    #create a composite image that includes the webcam
    composite = frame.copy()
    
    #add the letters
    #make a list of letter positions
    letter_positions = []
    for letter in range(150):
        x_position = position + letter*120
        y_position = 150
        xy = x_position, y_position
        cv2.putText(composite,chr(40+letter),xy, font, 2,color,3)
        letter_positions.append((chr(40+letter),xy))
        #if there is a letter selected, make that letter green
        if letter_selected:
            cv2.putText(composite, closest_letter, close_letter_position, font, 2, (255,0,0), 3)
    #add a line to show where the keyboard starts
    cv2.line(composite, (composite.shape[1],200), (0,200), color, 2)

    #find the background
    #look only at the keyboard part of the frame
    look = frame[50:200, 0:frame.shape[1]]
    fgmask = fgbg.apply(look)
    

    #define apparent_motion as false
    apparent_motion = False
    letter_selected = False
    previous_position = hand_position
    #find the largest contour in the fgmask image
    b,a,c = cv2.findContours(fgmask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    #draw a circle aroudn the contour
    for cnt in a:
        (x,y),radius = cv2.minEnclosingCircle(cnt)
        center = (int(x),int(y))
        area = cv2.contourArea(cnt)
        if area > 1000 and area < 2000:
            radius = int(radius)
            cv2.circle(composite,center,radius,(0,120,255), thickness=5)
            cv2.line(composite, (center[0]-50,center[1]), (center[0]+50,center[1]), (0,0,0),3)
            cv2.line(composite, (center[0],center[1]-50), (center[0],center[1]+50), (0,0,0),3)
            letter_selected = True
            #find the closest letter
            closest_letter = 'a'
            min_distance = 100000
            for letter_tuple in letter_positions:
                letter_position = letter_tuple[1]
                if distance(letter_position, center) < min_distance:
                    closest_letter = letter_tuple[0]
                    min_distance = distance(letter_position, center)
                    close_letter_position = letter_position
                    
            letter_buffer.append(closest_letter)
    
        #determine if there is apparent motion (swiping)
        if area > 2000:
            hand_position = center
            if previous_position != (0,0):
                apparent_motion = True
                if previous_position[0] > hand_position[0]:
                    dirrection = 'Left'
                    position -=100
                if previous_position[0] < hand_position[0]:
                    dirrection = 'Right'
                    position += 100

            previous_position = hand_position
    #if a letter has been selected for 10 frames, write the letter and clear the buffer
    for letter in letter_buffer[20:]:
        if letter == closest_letter:
            word += letter
            letter_buffer = []
    #write the word
    cv2.putText(composite, word, (50,50), font, 2, (0,0,0), 4)
    #show the various images and wait
    #cv2.imshow('fgmask',fgmask)
    #cv2.imshow('frame', frame)
    cv2.imshow('composite', composite)
    out.write(composite)
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break
cap.release()
cv2.destroyAllWindows()