from PIL import Image
import os

dir = os.path.dirname(__file__)
print(dir)

for imageFile in os.listdir(dir + '\image_png\\coin\\coin3\\'):
    # Open the image file
    # imageFile = dir + '\image_png\\' + imageFile
    image = Image.open(dir + '\image_png\\coin\\coin3\\' + imageFile)

    # Get the image dimensions (width and height)
    width, height = image.size

    # Convert the image to binary data
    image_data = image.tobytes()

    # Specify the output binary file
    output_file = dir + '\image_bin\\coin\\' + imageFile.split('.')[0] + '.bin'

    # Open the output file in binary write mode ('wb')
    with open(output_file, 'wb') as f:
        # Write the image dimensions as binary data
        f.write(width.to_bytes(4, byteorder='little'))
        f.write(height.to_bytes(4, byteorder='little'))
        
        # Write the image data
        f.write(image_data)
        
    print(width.to_bytes(4, byteorder='little'),height.to_bytes(4, byteorder='little'))

    print(f'Image dimensions: {width}x{height}')
    print('')
    # print(image_data)
    print(f'Image data and dimensions written to {output_file}')
