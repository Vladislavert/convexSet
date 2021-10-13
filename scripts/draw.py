#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Aug  1 22:49:39 2021

@author: argus
"""

from re import L
import sys
from vispy import app, scene
import socket
import struct
import numpy as np
import threading
# import tkinter as tk
# временно вносим интересующую переменную вектора состояния сюда
index = 0


class plotter():

    def __init__(self):
        self.data = []
        self.time = []
        self.canvas = scene.SceneCanvas(keys='interactive', show=True)
        self.grid = self.canvas.central_widget.add_grid(spacing=0)
        self.viewbox = self.grid.add_view(row=0, col=1, camera='panzoom')

        # add axes
        x_axis = scene.AxisWidget(orientation='bottom')
        x_axis.stretch = (1, 0.1)
        self.grid.add_widget(x_axis, row=1, col=1)
        x_axis.link_view(self.viewbox)
        y_axis = scene.AxisWidget(orientation='left')
        y_axis.stretch = (0.1, 1)
        self. grid.add_widget(y_axis, row=0, col=0)
        y_axis.link_view(self.viewbox)
        self.viewbox.camera.set_range((0, 1000), (-100, 100))

        self.host = '127.0.0.1'
        self.port = 3001
        self.msgLen = 136
        self.addr = (self.host, self.port)
        self.udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.udp_socket.bind(self.addr)
        # debug
        # N = 200
        # self.color = np.ones((N, 4), dtype=np.float32)
        # self.color[:, 0] = np.linspace(0, 1, N)
        # self.color[:, 1] = self.color[::-1, 0]

        self.currentDataIndex = index
        # self.pos = [[0, 0], [1, 1], [2, 2]]
        # self.pos = np.array([[0, 0], [1, 1], [2, 2]])
        # self.pos = np.zeros((20000, 2), dtype=np.float32)
        # line1 = scene.Line(self.pos, self.color, parent=self.viewbox.scene)
        # pos = np.zeros((N, 2), dtype=np.float32)
        pos = np.array([[0, 0], [1, 1], [2, 2]])
        # pos = [[0, 0], [1, 1], [2, 2]]
        # poss = np.array(pos)
        self.LastTime = 0
        self.line = scene.Line(pos, color=(0, 1, 1, 1),
                               parent=self.viewbox.scene)

        # self.stateVector = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
        self.point = [[]]
        self.result_point = [[]]

        rcv_thread = threading.Thread(target=self._reciveData,
                                      name="rcv_thread")
        rcv_thread.start()

    def _reciveData(self):
        while True:
            # print('wait data...')
            # recvfrom - получает UDP сообщения
            conn, addr = self.udp_socket.recvfrom(self.msgLen)
            # print('client addr: ', addr)
            # print(conn)
            self.stateVector = self._convertMessage(conn)
            if self.stateVector[-1] < self.LastTime:
                self.data = []
                self.time = []
                self.data.append(self.stateVector)
                self.time.append(self.stateVector[-1])
                # self.line = scene.Line(self.posInit, color=(0, 1, 1, 1),
                #                        parent=self.viewbox.scene)

            self.data.append(self.stateVector)
            self.time.append(self.stateVector[-1])
            self.LastTime = self.stateVector[-1]

    def _convertMessage(self, data):
        revData = bytearray(reversed(data))
        decodeData = list(
            reversed(struct.unpack("!dd", revData)))
        return decodeData

    def startPlotter(self):
        timer = app.Timer()
        timer.connect(self._updatePlot)
        # timer.start(step, totalTime)
        timer.start()
        app.run()

    def _updatePlot(self, ev):
        print(self.stateVector)
        self.currData = [i[self.currentDataIndex] for i in self.data]
        # print(self.currData)
        # print(self.time)
        dataPlot = np.array([self.time, self.currData]).T
        # print(dataPlot)
        # print(np.array(
        #     self.time, self.currData).T)
        # self.data.append([self.pseudoTime, np.sin(self.pseudoTime)])
        self.line.set_data(pos=dataPlot, color=(0, 1, 1, 1))
        # self.pseudoTime += 1




if __name__ == '__main__' and sys.flags.interactive == 0:
    # form = MainForm()
    plot = plotter()
    plot.startPlotter()
    # form.start()
