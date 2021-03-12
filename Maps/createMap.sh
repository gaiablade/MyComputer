map_file=$1
output_file=`echo ${map_file} | sed "s/\(\w*\)\.tmx/\1.mf/"`

echo "File: ${output_file}"

sed "1,3d" $map_file > $output_file

sed -i 's/^.*width=\"\([0-9]\+\)\".*height=\"\([0-9]\+\)\".*$/\1, \2/' $output_file

sed -i '2d' $output_file

sed -i '$d' $output_file

sed -i '$d' $output_file

sed -i '$d' $output_file