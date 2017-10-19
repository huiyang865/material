from docx import Document
import os

updated_box_file = open('./data/math_data_updated.box', 'wb')

# 获取box文件
box_text = ''
pathDir = os.listdir('./data/txt_box/')
pathDir.sort(key= lambda x:int(x[8:-4]))
for box_file in pathDir:
    child = os.path.join('%s%s' % ('./data/txt_box/', box_file))
    text_content = open(child, 'rb').read().decode('utf-8').strip()
    box_text += text_content + '\r\n'


box_text = box_text.split('\r\n')
box_num = 0
box_line = ''

html_dir = os.listdir('./data/alltxt_input/')
tag = 0
for file_path in html_dir:
    tag += 1
    # if tag >= 100:
    #     break
    fopen = open('./data/alltxt_input/' + file_path, 'rb')
    content_lines = fopen.read().decode('utf-8')
    for eachLine in content_lines.split('\n'):
        each_box_line = ''
        if '比较大小：            （填“＞”、“=”或“＜“）．' in eachLine:
            eachLine = eachLine.replace('（', '')
        if box_num < len(box_text)-1:
            for each_word in eachLine: # 每行数据
                if each_word == ' ' or each_word == ' ' or each_word == ' ' or \
                                each_word == '　' or each_word == '' or each_word == '':
                    continue
                if box_num +1 == len(box_text)-1:
                    box_num += 1
                    break
                # while int(box_text[box_num].split(' ')[2]) - int(box_text[box_num].split(' ')[0]) == 23 or \
                #                 int(box_text[box_num].split(' ')[2]) - int(box_text[box_num].split(' ')[0]) == 22:
                #     if int(box_text[box_num+1].split(' ')[1]) != int(box_text[box_num].split(' ')[1]):
                #         box_num += 1
                #     else:
                #         break
                box_line += each_word + ' ' + box_text[box_num] + '\r\n'
                if len(box_text[box_num+1].split(' ')) > 2:
                    if box_text[box_num].split(' ')[1] != box_text[box_num+1].split(' ')[1]:
                        box_line += '	' + ' ' + str(int(box_text[box_num].split(' ')[0])+60) + ' ' + \
                                    box_text[box_num].split(' ')[1] + ' ' + str(int(box_text[box_num].split(' ')[2])+60) \
                                    + ' ' + box_text[box_num].split(' ')[3] + ' ' + box_text[box_num].split(' ')[4] + '\r\n'
                box_num += 1
            if len(box_text[box_num+1].split(' ')) > 2:
                if box_text[box_num].split(' ')[1] != box_text[box_num+1].split(' ')[1]:
                    box_line += '	' + ' ' + str(int(box_text[box_num].split(' ')[0])+60) + ' ' + \
                                box_text[box_num].split(' ')[1] + ' ' + str(int(box_text[box_num].split(' ')[2])+60) \
                                + ' ' + box_text[box_num].split(' ')[3] + ' ' + box_text[box_num].split(' ')[4]+ '\r\n'
            box_num += 1


updated_box_file.write(box_line.encode('utf-8'))
