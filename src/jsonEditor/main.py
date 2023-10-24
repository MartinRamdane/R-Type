#!/usr/bin/env python3
import PySimpleGUI as psg
import json
import sys
from pathlib import Path

def create_modify_row(row_counter, value):
    row =  [psg.pin(
        psg.Col([[
            psg.InputText(default_text=value, size=(20,1), key=('-MODIFY-', row_counter))]],
        key=('-ROW-', row_counter),
        ))]
    return row

def create_combo_row(row_counter, value):
    print(f"Value: {value}")
    combo =  [psg.pin(
        psg.Col([[
            psg.Combo(value, font=('Arial Bold', 14),  expand_x=True, enable_events=True,  readonly=True, key=('-COMBO-', row_counter))]],
        key=('-ROW-', row_counter),
        ))]
    return combo

def create_simple_row(row_counter, value):
    row =  [psg.pin(
        psg.Col([[
            psg.Text(f'{value}', key=('-STATUS-', row_counter))]],
        key=('-ROW-', row_counter)
        ))]
    return row

def recursive_json_reader(jsonFile, window, row_counter):
    if isinstance(jsonFile, dict):
        for Key, Value in jsonFile.items():
            window.extend_layout(window['-ROW_PANEL-'], [create_simple_row(row_counter, Key)])
            recursive_json_reader(Value, window, row_counter)
    elif isinstance(jsonFile, list):
        for element in jsonFile:
            window.extend_layout(window['-ROW_PANEL-'], [create_combo_row(row_counter, element)])
            return
    else:
        window.extend_layout(window['-ROW_PANEL-'], [create_modify_row(row_counter, jsonFile)])
        print(f"Value: {jsonFile}")

def main(jsonList):
    lst = psg.Combo(jsonList, font=('Arial Bold', 14),  expand_x=True, enable_events=True,  readonly=True, key='-COMBO-')
    layout = [[lst, psg.Button('Load', key='-LOAD-')], [psg.Column([create_simple_row(0, 'Json Content:')], k='-ROW_PANEL-')]]

    window = psg.Window('Json Editor',
        layout,  use_default_focus=False, font='15')

    row_counter = 0
    while True:
        event, values = window.read()
        if event == psg.WIN_CLOSED or event == '-EXIT-':
            break
        if event == '-LOAD-':
            with open(values['-COMBO-']) as json_file:
                data = json.load(json_file)
                row_counter += 1
                recursive_json_reader(data, window, row_counter)
    window.close()

if __name__ == "__main__":
    jsonList = []
    for path in Path('./config').rglob('*.json'):
        jsonList.append(path)
    main(jsonList)
