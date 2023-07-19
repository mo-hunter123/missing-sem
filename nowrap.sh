#!/usr/bin/perl -w

my $cols=`/bin/tput cols`; chomp $cols;

while(<>){
  chompnl($_); my $tmp=$_; my $add=0;
  while($tmp=~/(.*?)(\033\[[\d\;]+m)(.*)/) {
    $add+=length($2) if(length($1)<$cols);
    $tmp=$1 . $3;
  }
  while($tmp=~/(.*?)\t(.*)/) {
    my $spc=8-(length($1) % 8);
    $tmp=$1 . ( ' ' x $spc ) . $2;
    $add-=($spc-1);
  }

  print substr($_,0,$cols+$add) . "\n";
}

# chomp() on unix doesn't eat "\r"...
sub chompnl {   # Warning: don't stuff up $1
  chop $_[0] while((substr($_[0],-1) eq "\015")||(substr($_[0],-1) eq "\012"));
} # chompnl