import sys
from PIL import Image, ImageDraw, ImageFont

def create_number_image(number, width, height, font_size):
    # Create a white image
    image = Image.new("RGB", (width, height), "white")

    # Initialize drawing context
    draw = ImageDraw.Draw(image)

    # Load a font 
    font = ImageFont.truetype("arial.ttf", font_size)

    # Calculate text position to center it
    text = str(number)
    text_width, text_height = draw.textsize(text, font=font)
    position = ((width - text_width) // 2, (height - text_height) // 2)

    # Draw the number on the image
    draw.text(position, text, fill="black", font=font)

    # Save the image as a PNG file
    image.save(f"{number}.png")
    print(f"Image of number saved!")

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print("Wrong input arguments!")
        sys.exit(1)

    # Parse command-line arguments
    try:
        number = sys.argv[1]
        width = int(sys.argv[2])
        height = int(sys.argv[3])
        font_size = int(sys.argv[4])
    except ValueError:
        print("Width, height, and font_size must be integers.")
        sys.exit(1)

    # Call the function to create the image
    create_number_image(number, width, height, font_size)