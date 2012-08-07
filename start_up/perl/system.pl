#!/usr/bin/perl -w

print "Please input the file: ";
$file = <STDIN>;
chomp $file;

system("vim $file");
print "You have closed the vim editor!\n";
