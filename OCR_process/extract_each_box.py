updated_box_file = open('./data/math_data_updated.box', 'rb')
text_content = updated_box_file.read().decode('utf-8').strip()

box_page = 15
reault = ''
for each_box in text_content.split('\r\n'):
    try:
        if int(each_box.split(' ')[5]) == box_page:
            reault += each_box.split(' ')[0] + ' ' + each_box.split(' ')[1] + ' ' + each_box.split(' ')[2] + ' ' \
                      + each_box.split(' ')[3] + ' ' + each_box.split(' ')[4] + ' 0' + '\r\n'
    except:
        print(each_box)
open('./data/image_math_data.pdf_'+str(box_page)+'.box', 'wb').write(reault.encode('utf-8'))
