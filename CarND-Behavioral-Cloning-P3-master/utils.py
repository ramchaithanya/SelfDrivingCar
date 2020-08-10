#!/usr/bin/env python
# coding: utf-8

import cv2, os
import matplotlib.image as mpimg

IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CHANNELS = 64, 64, 3

def crop(image):
    return image[69:-25]

def resize(image):
    return cv2.resize(image, (IMAGE_WIDTH, IMAGE_HEIGHT), cv2.INTER_AREA)

def rgb2yuv(image):
    return cv2.cvtColor(image, cv2.COLOR_RGB2YUV)

def preprocess(image):
    
    image = crop(image)
    image = resize(image)
    image = rgb2yuv(image)
    return image
