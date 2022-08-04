473#  -*- coding: utf-8 -*-
"""
Created on Tue Apr  5 14:27:29 2022

@author: Haroon Nawaz
"""
import time
import tkinter as tk
# import english-words
# from PyDictionary import PyDictionary
# dictionary=PyDictionary()
from pynput import keyboard
# with open("google-10000-english-usa-no-swears.txt") as f:
#     words = f.readlines()
with open("20k.txt") as f:
    words = f.readlines()
def updateState(event):
    print("Update state")
def removeKey():
    print("Remove Key")
for i in range(len(words)):
    words[i] = words[i][0:-1]

sentence = []
keystrokes = []
current_index = 0
potential_words = []
potential_word_depth = 10

keyboardToChar = {1: ["q", "a", "z"], 2: ["w", "s", "x"], 3: ["e", "d", "c"], 4: ["r", "f", "v", "t", "g", "b"], 
                  7: ["y", "h", "n", "u", "j", "m"], 8: ["i", "k"], 9: ["o", "l", "p"], 0:[]}

sentence_gui = ""
window = tk.Tk()
sentence_frame = tk.Frame()
words_frame = tk.Frame()
sentence_label = tk.Label(master = sentence_frame, text = sentence_gui)
sentence_label.pack()
sentence_frame.pack()

def FindWords(keystrokes):
    potential_words = []
    while (len(potential_words) < potential_word_depth):
        for j, word in enumerate(words):
            word_fits = True
            if(j == len(words)-1):
                break
            if(len(potential_words) >= potential_word_depth):
                    break
            for i, keystroke in enumerate(keystrokes):
                try:
                    if(word[i] not in keyboardToChar[keystroke]):
                        word_fits = False
                        break
                except:
                    word_fits = False
                    break
            if(word_fits):
                potential_words.append(word)
            if(len(potential_words) >= potential_word_depth):
                    break
    #potential_words.sort(key=len)
    #potential_words = potential_words[0:potential_word_depth]
    print("potential", potential_words)
    return potential_words
        
def on_press(key, keystrokes, sentence, potential_words, potential_word_depth):
    global current_index
    try:
        keystrokes.append(int(key.char))
        #print(keystrokes)
        potential_words = FindWords(keystrokes)

    except AttributeError:
        if(key == keyboard.Key.space):
            potential_words = FindWords(keystrokes)
            #print(potential_words)
            sentence.append(potential_words[current_index])
            
            global sentence_gui
            sentence_gui = ' '.join(sentence)
            sentence_label.configure(text=sentence_gui)
            keystrokes.clear()
            current_index = 0
            print("Sentence:", sentence)
        if(key == keyboard.Key.backspace):
            if(bool(keystrokes)):
                keystrokes.pop()
            potential_words = FindWords(keystrokes)
            print(potential_words)
        if(key == keyboard.Key.right):
            print("Right")
            current_index = (current_index + 1) % potential_word_depth
        if(key == keyboard.Key.left):
            print("Left")
            current_index = (current_index - 1) % potential_word_depth
        # print('special key pressed: {0}'.format(
        #     key))

def on_release(key):
    # print('Key released: {0}'.format(
    #     key))
    if key == keyboard.Key.esc:
        # Stop listener
        return False


on_press_func = lambda key: on_press(key, keystrokes, sentence, potential_words, potential_word_depth)
listener = keyboard.Listener(
        on_press=on_press_func,
        on_release=on_release)
listener.start()


window.mainloop()

# def readKey(event):1783 
#     char = keyboard.read_key()
#     print(char)
#     print(event.name)
#     print(event)
#     print("here")
# keyboard.on_release(readKey)

    
# while(True):
#     try:  # used try so that if user pressed other than the given key error will not be shown
#         print("sleeping")
#         time.sleep(5)
#         print("slept")
#     except:
#         print("#######")
 #       break  # if user pressed a key other than the given key the loop will break
# while True:
#     if keyboard.read_key() == "p":
#         print("You pressed p")
#         break

# while True:
#     print(keyboard.read_key())
#     if keyboard.is_pressed("q"):
#         print("You pressed q")
#         break
        
# keyboard.on_press_key("r", lambda _:print("You pressed r"))
    
    
    