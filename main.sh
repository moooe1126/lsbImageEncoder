RED='\033[0;31m'
gcc -o steggo core/Image.c core/steggo.c -lm
gcc -o extract core/Image.c core/extract.c -lm

while [ 1 -eq 1 ]
do
echo "what would you like to do: "
echo "1) encode data into an image"
echo "2) retreve data from .png image"
echo "3) upload image"
echo "4) exit"
read choice

if [ $choice -eq 1 ]
then
  find $directory -type f -name '*.png'
  find $directory -type f -name '*.jpg'
  find $directory -type f -name '*.jpeg'
  read -p "enter the filename of the imagstrlene you would like to hide data into: " img
  read -p "enter the data you would like to encode into the image: " data
  read -p "enter the key you would like to encode the image with: " key

  clear
  chmod +x steggo
  ./steggo "$img" "$data" "output.png" "$key"
  tput setaf 1; echo "output image stored as output.png"
  tput sgr0
fi
if [ $choice -eq 2 ]
then
  find $directory -type f -name '*.png'
  read -p "enter the filename of the image you would like to retreve data from: " data_img
  read -p "enter the key you would like to decrypt the image with " key_ret
  
  clear
  echo ""
  ./extract "$data_img" "$key_ret"
  echo ""
  echo ""
fi
if [ $choice -eq 3 ]
then
read -p "paste an image url : " new_image
read -p "what would you like to name this image: " new_image_name
wget "$new_image" "-O" "$new_image_name"
fi
if [ $choice -eq 4 ]
then
  clear
  exit
fi
done