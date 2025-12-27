export LC_ALL=C
echo preparing offset and feature_value files
cp ../c_data/gen_fe_val_off.c .
cc -g -o gen_fe_val_off.out gen_fe_val_off.c ../c_data/getfileword.c ../c_data/getline.c
./gen_fe_val_off.out
rm gen_fe_val_off.c
#noun_feature_value contains list of noun types & their feature values. This is for Telugu
cat feature_value noun_feature_value >jnk
mv jnk feature_value
sed -e '/^noun_/d
        /^noun/d
        /^adj,/d
        /^adv,/d
        /^avy,/d
        /numeric/d
        /pronoun/d
        /pronoun_/d
        /_pronoun_/d' offset > jnk
cat jnk noun_offset > jnk2
mv jnk2 offset
rm jnk
echo preparing suff_info
cp ../c_data/suff_gen.c . 
cc  -g -o suff_gen.out suff_gen.c ../c_data/getfileword.c
./suff_gen.out 1
rm suff_gen.c
echo sorting suff_info
sh suff.sh
#rm suff_info.bak
echo separating suff and add from other information
sh feature_value.sh
sh cat.sh
#rm cvt.out
rm gen_fe_val_off.out
#rm offset
#rm feature_value
rm suff_gen.out
