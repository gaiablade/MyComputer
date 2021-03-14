map_file=$1
output_file=`echo ${map_file} | sed "s/\(\w*\)\.tmx/\1.mf/"`

echo "File: ${output_file}"

# Delete all lines except the layer attribute:
sed -n "/^ <layer.*$/p" $map_file > $output_file

# 
sed -i 's/^.*width=\"\([0-9]\+\)\".*height=\"\([0-9]\+\)\".*$/\1, \2/' $output_file
sed -n "/^\([0-9]\+,\)\+[0-9],\?$/p" $map_file >> $output_file