RED='\033[0;31m'


while [ 1 -eq 1 ]
do
echo "what would you like to do: "
echo "1) encode data into .png image"
echo "2) retreve data from .png image"
echo "3) exit"
read choice

if [ $choice -eq 1 ]
then
  find $directory -type f -name '*.png'
  read -p "enter the filename of the image you would like to hide data into: " img
  read -p "enter the data you would like to encode into the image: " data
  clear
  chmod +x steggo
  ./steggo "$img" "$data"
  tput setaf 1; echo "output image stored as output.png"
  tput sgr0
fi
if [ $choice -eq 2 ]
then
  find $directory -type f -name '*.png'
  read -p "enter the filename of the image you would like to retreve data from: " data_img
  clear
  echo ""
  ./extract "$data_img"
  echo ""
  echo ""
fi

if [ $choice -eq 3 ]
then
  clear
  exit
fi
done