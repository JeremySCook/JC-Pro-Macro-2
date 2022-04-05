$fn=25;

Outside_Width=18;
Outside_Height=10;
Spindle_Diameter=5.25;
Line_Width=1.15;
Line_Length=4;
Wall_Thickness=1.5;
Top_Width=13.5;
Symbol_Thickness=0.5;
Key_Symbol="9";


// Top Layer
translate([0,0,Outside_Height])
difference(){
Capshape(Symbol_Thickness,Top_Width,Wall_Thickness,Top_Width-Symbol_Thickness);
// Symbol on Key Cap
linear_extrude(height=Symbol_Thickness)
text(Key_Symbol,valign="center",halign="center");
}

// Basic Cap Shape
difference(){
Capshape(Outside_Height,Outside_Width,Wall_Thickness,Top_Width);
// Hollow it out
Capshape(Outside_Height-Wall_Thickness,Outside_Width-Wall_Thickness*2,Wall_Thickness,Top_Width-Wall_Thickness*2);
}

difference(){
// Spindle
cylinder(h=Outside_Height,d=Spindle_Diameter);
// Slots
union(){
translate([Line_Width/-2,Line_Length/-2,0])
cube([Line_Width,Line_Length,Outside_Height-Wall_Thickness]);
translate([Line_Length/-2,Line_Width/-2,0])
cube([Line_Length,Line_Width,Outside_Height-Wall_Thickness]);
}
}


module Capshape(Height,Width,Thickness,Top){
linear_extrude(height=Height,scale=Top/Width){
translate([0-Width/2,0-Width/2,0]){
hull(){
translate([Thickness/2,Thickness/2,0])
circle(d=Thickness);
translate([Width-Thickness/2,Thickness/2,0])
circle(d=Thickness);
translate([Width-Thickness/2,Width-Thickness/2,0])
circle(d=Thickness);
translate([Thickness/2,Width-Thickness/2,0])
circle(d=Thickness);
}
}
}
}