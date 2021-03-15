map_file=$1
output_file=`echo ${map_file} | sed "s/\(\w*\)\.tmx/\1.mf/"`

echo "File: ${output_file}"

# Delete all lines except the layer attribute:
sed -n "/\(^ <layer.*$\)\|\(^\([0-9]\+,\)\+[0-9],\?$\)/p" $map_file > $output_file

# Extract width and height onto a line:
sed -i 's/^.*width=\"\([0-9]\+\)\".*height=\"\([0-9]\+\)\".*$/\1, \2/' $output_file

# Remove empty lines
sed -i '/^$/d' $output_file


# Get all lines with map data:
#sed -n "/^\([0-9]\+,\)\+[0-9],\?$/p" $map_file >> $output_file