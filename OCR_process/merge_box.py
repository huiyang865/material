box_file1 = open('E:/jTessBoxEditorFX/tesseract-ocr/temp_roman/chi_sim.SIMSUN_roman.exp0.box', 'rb').read().decode('utf-8')
box_file2 = open('E:/jTessBoxEditorFX/tesseract-ocr/temp_roman/math_data.box', 'rb').read().decode('utf-8')

box_content = box_file1 + '\n'
box1_page_num = 0
for line in box_file1.split('\n'):
    if len(line) > 0:
        page_num = int(line.split(' ')[len(line.split(' '))-1])
    if page_num > box1_page_num:
        box1_page_num = page_num

box1_page_num += 1
for line in box_file2.split('\r\n'):
    if len(line) > 0:
        page_num1 = int(line.split(' ')[len(line.split(' '))-1])
        sub_line = ''
        for i in range(len(line.split(' '))-1):
            sub_line += line.split(' ')[i] + ' '
        box_content += sub_line + str(page_num1+box1_page_num) + '\n'

open('E:/jTessBoxEditorFX/tesseract-ocr/temp_roman/chi_sim.SIMSUN_roman.exp1.box', 'bw').write(box_content.encode('utf-8'))

print('merge success!')