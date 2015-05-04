"README:
Created by Dickson Chui @vicksonzero

License:
  You are basically free to do anything 
  including commercial use, 
  but you have to give credit to me 
  (Dickson Chui, @vicksonzero) 
  somewhere easy to see

since I am not allowed to use comments, 
I am going to use this loose 
hanging string to comment my code";


"Cookie Hacker";

"

Consider going to:
github.io/vicksonzero/cookieHacker
for the full code





"

"==============================";
"Game init - only run once";
"contains description to reserved variables";
"If it is the first run,";
if var_a == 0 {

	"B = Button state";
	"right, up, left, down, A, B, Konami";
	var_b = [0,0,0,0,0,0,0];
	

	"User decision / pointer location";
	"range from 0 to number of unlocked shops";
	"-1 = disabled";
	var_d = -1;
	

	"C = cookies";
	"0 = current cookies count";
	"1 = total cookies made";
	"2 = konami code";
	"3 = konami progress";
	"4 = game progress descriptions";
	"5 = end game flag";
	"6 = count unlocked shops"
	var_c = [0,0,0,0,0,0,0];
	var_c[2] = [];
	var_c[2].push(function -> up());
	var_c[2].push(function -> up());
	var_c[2].push(function -> down());
	var_c[2].push(function -> down());
	var_c[2].push(function -> left());
	var_c[2].push(function -> right());
	var_c[2].push(function -> left());
	var_c[2].push(function -> right());
	var_c[2].push(function -> b_btn());
	var_c[2].push(function -> a_btn());

	var_c[3] = 0;

	var_c[4] = [];
	var_c[4].push([0,                ""]);
	var_c[4].push([30,               "You are getting into business"]);
	var_c[4].push([85,               "You opened a small shop in town"]);
	var_c[4].push([150,              "Kids like your cookies"]);
	var_c[4].push([300,              "People queue up for your cookies"]);
	var_c[4].push([600,              "You work hard to improve youe recipe"]);
	var_c[4].push([1000,             ""]);
	var_c[4].push([1000,             ""]);
	var_c[4].push([1000,             ""]);
	var_c[4].push([200 000,          "You appear on the cover of Timed magazine"]);
	var_c[4].push([400 000,          "You visit jungle temples for cookie recipes"]);
	var_c[4].push([1000 * 1000,      "You are a million-cooki-aire"]);
	var_c[4].push([2 * 1000 * 1000,  "You are president of several worlds"]);
	var_c[4].push([5 * 1000 * 1000,  "You had a recurring nightmare..."]);
	var_c[4].push([6 * 1000 * 1000,  "A nightmare about 1000 fingers..."]);
	var_c[4].push([10 * 1000 * 1000, "1000 fingers on the same hand"]);

	var_c[5] = 0;


	"A is recycled from checking first run";
	"A = shops list";
	"Shop entry format:";
	"0 = Name";
	"1 = Cost";
	"2 = cookies per tick";
	"3 = state: unlocked?";
	"4 = list of shop instances";
	"5 = icon of shop";
	"see function2 for shop insance format";
	var_a = [];
	var_a.push(["Finger",   15,       1,     false,[],"icon"]);
	var_a.push(["Grandma",  100,      2,     false,[],"icon"]);
	var_a.push(["Farm",     500,      20,    false,[],"icon"]);
	var_a.push(["Factory",  5000,     150,   false,[],"icon"]);
	var_a.push(["Shipment", 100 000,  4000,  false,[],"icon"]);
	var_a.push(["Portal",   500 000,  9999,  false,[],"icon"]);
	var_a.push(["Hackpad",  999 999,  55555, false,[],"icon"]);

	"E = count unlocked shop";
	var_e=0;

	"G = upgrade rate [numerator, denominator]";
	var_g = [15,100];

	"N = Timekeeper[
		fps,
		startTime,
		currentTime,
		elapsedTime
	]";
	var_n = [2, time(), time(), 0];
	"frequency to period";
	var_n[0] = 1000/var_n[0];

	"H = rain object. holds raindrops";
	var_h = [];

	"O = reserved for buffer";
	"I,J = reserved for iteration";
	var_o = 0;
	var_i = 0;
	var_j = 0;
}

"==============================";
"functions";
function f4: var_a {
	"Push an icon into the rain";
	"Rain drop:";
	"0 = icon";
	"1 = startY";
	var_o = "";
	var_i = random(50);
	while var_i-- > 0 {
		var_o = var_o + " ";
	}
	return [ var_o + var_a, 0];
}


function f1: var_c, var_a {
	"make cookie";
	"C = cookie counter object";
	"Pass by reference";
	"A = amount";
	var_c[0] = var_c[0] + var_a;
	var_c[1] = var_c[1] + var_a;
}

function f2: var_d {
	"Build a shop instance";
	"D = shop type";
	"Shop instance:";
	"0 = cookie per tick";
	"1 = Birthday";
	return [var_d[2], time()];
}

function f3: var_d, var_a {
	"Upgrade a shop type";
	"D = shop type";
	"A = upgrade rate";
	
	"Update cost:";
	var_o = var_d[1] * var_a[0] / var_a[1];
	if var_o < 1 {
		var_o = 1;
	}
	var_d[1] = var_d[1] + var_o;

	"Update cookie per tick";
	if false{
		var_o = var_d[2] * var_a[0] / var_a[1];
		if var_o < 1 {
			var_o = 1;
		}
		var_d[2] = var_d[2] + var_o;
	}
}

"==============================";
"Game rule";

"unlock shops";
"for all shop types";
var_i=0;
while var_i < var_a.length {
	"if not built";
	if !var_a[var_i][3] {
		"if have enough money to unlock";
		"i.e. 70% of cost";
		if var_c[0] > var_a[var_i][1] * 7 / 10 {
			"unlock shop";
			var_a[var_i][3] = true;
			"count unlocked shops";
			var_e++;
			"unlock pointer if not yet";
			if var_d == -1 {
				var_d = 0;
			}
		}
	}
	var_i++;
}

"Auto make cookies";
"current time";
var_n[1] = time();
"for each shop instance (double for-loop)";
foreach var_i in var_a {
	foreach var_j in var_i[4] {
		"if waited enough time";
		if var_n[1] - var_j[1] > var_n[0]{
			"update cookie count";
			f1(var_c, var_j[0]);
			"reset timer for next iteration";
			var_j[1] = var_j[1] - var_n[0];
		}
	}
}






"==============================";
"view";

"background";
"show and update raindrops";
var_i = 0;
while var_i < var_h.length {
	draw_text(0, var_h[var_i][1], var_h[var_i][0]);
	"move raindrop down";
	var_h[var_i][1]++;
	"delete raindrop if out of screen";
	if var_h[var_i][1] > height() {
		var_h.remove(var_i);
		"no need to do var_i++";
		"if remove() is called";
	}
	else{
		var_i++;
	}
}

"show cookies count";
draw_text(0,0,"Cookies: " + var_c[0]);

"if not yet game over";
if var_c[5] == 0 {
	
	"show shop list";
	var_i=0;
	while var_i < var_a.length {
		"if unlocked";
		if var_a[var_i][3]{
			var_o = var_a[var_i][4.length] + "x ";
			var_o = var_o + var_a[var_i][0];
			var_o = var_o + " (+" +var_a[var_i][2] + ")";
			var_o = var_o + " $" + var_a[var_i][1];
			draw_text(2, 4 + var_i, var_o);
		}
		var_i++;
	}

	"Show pointer";
	if var_d != -1 {
		draw_text(1, 4 + var_d, ">");
	}
}

"draw built shop instances";
"Wow... not enough variables to use...
time to use array for no reason";
"0 = string buffer";
"1 = count horizontal symbols";
"2 = line number";
var_o = ["",0,11];
"for each shop instance (double for-loop)";
foreach var_i in var_a {
	foreach var_j in var_i[4] {

		"add icon to list";
		var_o[0] = var_o[0] + var_i[5];

		"count; if this line is full";
		var_o[1]++;
		if var_o[1] == 15 {
			"flush and next line";
			draw_text(0,var_o[2], var_o[0]);
			var_o[1] = 0;
			var_o[2]++;
			var_o[0] = "";
		}

	}
}
"flush last line";
draw_text(0,var_o[2], var_o[0]);

"show game progress description";
"if current cookies is enough for next level";
if var_c[4].length > 1 {
	if var_c[0] > var_c[4][1][0] {
		"advance to next level";
		var_c[4].remove(0);
	}
}
draw_text(0, height()-1, var_c[4][0][1]);


"show god mode";
if var_b[6] == 100 {
	draw_text(width() - 6, 0, "God mode");
}



"==============================";
"Interactions";

"keydown(A)";
if a_btn() && var_b[4] == 0 {
	"if have at least 1 shop unlocked";
	if var_e > 0 {
		"if have enough money";
		if var_c[0] - var_a[var_d][1] > -1 {
			"buy the shop";
			
			"pay the money";
			var_c[0] = var_c[0] - var_a[var_d][1];

			"Create the shop and push to instance list";
			var_a[var_d][4].push( f2(var_a[var_d]) );

			"upgrade the shop type for next buy";
			f3(var_a[var_d], var_g);

			"Rain down a grandma";
			var_h.push( f4(var_a[var_d][5]) );
		}
	}
}

"keydown(B)";
if b_btn() && var_b[5] == 0{
	"make a cookie";
	f1(var_c, 1);

	"rain cookie";
	var_h.push( f4("cookie icon") );
}


"keydown(up, down)";
"move cursor up down";
if up() && var_b[1]==0 {
	if var_d > 0 {
		var_d --;
	}
}
if down() && var_b[3]==0 {
	if var_d + 1 < var_e {
		var_d ++;
	}
}


"Konami code";
"keyup(konami)";
"the current konami key changes everytime.";
"  because var_c[2] stores a list of ";
"  annonymous functions that checks differnet";
"  keys but the calling method is the same";
"notice the () after var_c[2][var_c[3]]";
"it means take the variable and call the function";
"  it is pointing at";

if var_b[6] == 1 && !var_c[2][var_c[3]]() {
	"advance konami code by 1";
	var_c[3]++;
	"if completes konami";
	if var_c[3] == var_c[2].length {
		"cheat here";
		var_c[0] = var_c[0] + 999999;
		"reset konami";
		var_c[3] = 0;
		"Lock konami, disabling it for 2nd use";
		var_b[6] = 100;
	}
}
"if press other buttons than konami";
if up() || down() || left() || right() || a_btn() || b_btn() {
	if var_b[6] == 0 && !var_c[2][var_c[3]]() {
		"reset konami";
		var_c[3] = 0;
	}
}



"==============================";
"button event lifecycles";
"check button down";
if right() && var_b[0] == 0 {
	var_b[0] = 1;
}
if up() && var_b[1] == 0 {
	var_b[1] = 1;
}
if left() && var_b[2] == 0 {
	var_b[2] = 1;
}
if down() && var_b[3] == 0 {
	var_b[3] = 1;
}
if a_btn() && var_b[4] == 0 {
	var_b[4] = 1;
}
if b_btn() && var_b[5] == 0 {
	var_b[5] = 1;
}
if var_b[6] == 0 && var_c[2][var_c[3]]() {
	var_b[6] = 1;
}


"check button up";
if ! right() && var_b[0]== 1 {
	var_b[0] = 0;
}
if ! up() && var_b[1]== 1 {
	var_b[1] = 0;
}
if ! left() && var_b[2]== 1 {
	var_b[2] = 0;
}
if ! down() && var_b[3]== 1 {
	var_b[3] = 0;
}
if ! a_btn() && var_b[4]== 1 {
	var_b[4] = 0;
}
if ! b_btn() && var_b[5]== 1 {
	var_b[5] = 0;
}
if var_b[6] == 1 && ! var_c[2][var_c[3]]() {
	var_b[6] = 0;
}









