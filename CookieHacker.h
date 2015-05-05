"README:"
"Cookie Hacker";
"Created by Dickson Chui @vicksonzero"

"
License:
  This piece of code is released 
  to the public domain. You can do 
  whatever you like with it.

  However, 
  If you are to directly modify my game,
  with most of the rules and implementations
  untouched, I appreciate that you save me 
  some credits.
"
"since I am not allowed to use comments, 
I am going to use this loose 
hanging string to comment my code";
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
	var_c[4].push([0,                "Press B to Bake cookies"]);
	var_c[4].push([2,                ""]);
	var_c[4].push([15,               "Press A to hire helpers"]);
	var_c[4].push([30,               "You are getting into business"]);
	var_c[4].push([85,               "You opened a small shop in town"]);
	var_c[4].push([150,              "Kids like your cookies"]);
	var_c[4].push([300,              "People queue up for your cookies"]);
	var_c[4].push([600,              "You work hard to improve your cookies"]);
	var_c[4].push([1000,             "You and your cookies appear on TV"]);
	var_c[4].push([2000,             "You travel worldwide for cookie recipes"]);
	var_c[4].push([4000,             "The mayor likes yuor cookies"]);
	var_c[4].push([8000,             "You start to surpass your rivals"]);
	var_c[4].push([12000,            "Your brand is well known in the country"]);
	var_c[4].push([40000,            "Your cookies become tourist attractions"]);
	var_c[4].push([80000,            "Your cookies sell worldwide"]);
	var_c[4].push([100000,           "You even have merchandise for your cookies"]);
	var_c[4].push([200 000,          "You appear on the cover of Timed magazine"]);
	var_c[4].push([400 000,          "You travel to the far East for cookie recipes"]);
	var_c[4].push([1000 * 1000,      "You are a million-cooki-aire"]);
	var_c[4].push([2 * 1000 * 1000,  "You are president of several worlds"]);
	var_c[4].push([4 * 1000 * 1000,  "You learnt how to live 573 lives"]);
	var_c[4].push([6 * 1000 * 1000,  "You had a recurring nightmare..."]);
	var_c[4].push([8 * 1000 * 1000,  "A nightmare about 1000 fingers..."]);
	var_c[4].push([11 * 1000 * 1000, "1000 fingers on the same hand"]);
	var_c[4].push([25 * 1000 * 1000, "..."]);
	"0 = in-game"
	"1 = end game animation part 1"
	"2 = end game animation part 2, end credits"
	"3 = End"
	var_c[5] = 0;
	"count unlocked shops";
	var_c[6] = 0;


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
	var_a.push(["Finger",   15,       1,     false, [], "icon"]);
	var_a.push(["Grandma",  100,      2,     false, [], "icon"]);
	var_a.push(["Farm",     500,      20,    false, [], "icon"]);
	var_a.push(["Factory",  5000,     150,   false, [], "icon"]);
	var_a.push(["Shipment", 70 000,   4000,  false, [], "icon"]);
	var_a.push(["Portal",   500 000,  9999,  false, [], "icon"]);
	var_a.push(["Hackpad",  999 999,  30000, false, [], "icon"]);

	"E = End game animation data";
	"0 = animation progress (y-value)";
	"1 = timer";
	"2 = anim fps"
	var_e=[];
	var_e.push( height() );
	var_e.push( time() );
	var_e.push(4);
	"frequency to period";
	var_e[2] = 1000 / var_e[2];

	"G = upgrade rate [numerator, denominator]";
	var_g = [16,100];

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
	"(Passed by reference)";
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

	"Increase cookie per tick";
	"disabled"
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
"If not yet game over"
if var_c[5] == 0 {
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
				var_c[6]++;
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
				var_j[1] = var_j[1] + var_n[0];
			}
		}
	}
	"Check winning conditions";
	if var_a[0][4].length == 105 || var_a[0][4].length > 105 {
		"End the game"
		var_c[5] = 1;
	}
}









"==============================";
"view";

"The ordering here is not done
according to logic, but to the
layering needed. things drawn
later come on the top
"
"background";
"show and update raindrops";
"all the time"
var_i = 0;
while var_i < var_h.length {
	draw_text(0, var_h[var_i][1], var_h[var_i][0]);
	"move raindrop down";
	var_h[var_i][1]++;
	"delete raindrop if out of screen";
	if var_h[var_i][1] > height() {
		var_h.remove(var_i);
		"no need to do var_i++
		if remove() is called";
	}
	else{
		var_i++;
	}
}

"show cookies count";
"showed in-game and end-game animation#1"

if var_c[5] < 2 {
	draw_text(0,0,"Cookies: " + var_c[0]);
}

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

"showed in-game and end-game animation#1"
if var_c[5] < 2 {
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

			"count; if this line is full,";
			var_o[1]++;
			if var_o[1] == 15 {
				"flush and prep for next line";
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
		if var_c[0] > var_c[4][1][0] || var_c[0] == var_c[4][1][0] {
			"advance to next level";
			var_c[4].remove(0);
		}
	}
	draw_text(0, height()-1, var_c[4][0][1]);
}


"End game animation";
if var_c[5] == 1 {
	"raining cookies";
	var_h.push( f4("cookie icon") );

	"draw a pile of cookies to fill the screen";
	var_o = "";
	while var_o.length < 40 {
		var_o = var_o + "cookie icon";
	}
	"number of lines of cookies"
	var_i = var_e[0];
	"draw from top of pile"
	while var_i < height() + 1 {
		"draw twice to cover up what's beneath";
		draw_text(0, var_i, var_o);
		draw_text(0, var_i, var_o);
		var_i++;
	}
	"add 1 more pile to the top every fps";
	"until it fills the screen"
	if var_e[0] > 0 {
		"if we have waited enough time"
		var_n[1] = time();
		if var_n[1] - var_e[1] > var_e[2] {
			"move the top upwards"
			var_e[0]--;
			"reset timer"
			var_e[1] = time();
		}
	}
	else{
		"Animation phase 2"
		var_c[5] = 2;
	}
}

"End game message";
"shown after cookies fill the screen, 
until end of time"
if var_c[5] > 1 {
	var_o = [];
	var_o.push("You spend day and night making ");
	var_o.push("  delicious cookies.");
	var_o.push("You find that having 1 finger");
	var_o.push("  is not enough.");
	var_o.push("You set out for more fingers");
	var_o.push("  just to make more cookies.");
	var_o.push("Until one day,");
	var_o.push("The Fingers are more important");
	var_o.push("Than the cookies themselves.");
	var_o.push("");
	var_o.push("The End");
	var_o.push("");
	var_o.push("");
	var_o.push("Cookie Hacker v1.3");
	var_o.push("By Dickson Chui");
	var_o.push("Feedbacks:");
	var_o.push("github.com/vicksonzero/");
	var_o.push("  cookieHacker");

	var_i = 0;
	while var_i < var_o.length {
		draw_text(1, 3 + var_i, var_o[var_i]);
		var_i++;
	}
}
"Animation phase 2"
if var_c[5] == 2 {
	"draw a pile of cookies to fill the screen";
	var_o = "";
	while var_o.length < 40 {
		var_o = var_o + "cookie icon";
	}
	"number of lines of cookies"
	var_i = var_e[0];
	"draw from bottom of pile (while counting the same way)"
	while var_i < height() + 1 {
		"draw twice to cover up what's beneath";
		draw_text(0, height() - var_i, var_o);
		draw_text(0, height() - var_i, var_o);
		var_i++;
	}
	"add 1 more pile to the top every fps";
	"until it fills the screen"
	if var_e[0] > 0 {
		"if we have waited enough time"
		var_n[1] = time();
		if var_n[1] - var_e[1] > var_e[2] {
			"roll the bottom upwards"
			var_e[0]++;
			"reset timer"
			var_e[1] = time();
		}
	}
	else{
		"final end"
		var_c[5] = 3;
	}
}




"show that you have used cheat";
if var_b[6] == 100 {
	draw_text(width() - 6, 0, "God mode");
}



"==============================";
"Interactions";



"if not yet game over"
if var_c[5] == 0{

	"keydown(A)";
	if a_btn() && var_b[4] == 0 {
		"if have at least 1 shop unlocked";
		if var_c[6] > 0 {
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
		if var_d + 1 < var_c[6] {
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
			if false {
				var_c[0] = var_c[0] + 999999;
			}
			if false {
				var_c[5] = 1;
			}
			"reset konami";
			var_c[3] = 0;
			"Lock and disable konami, but also enable other cheats";
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
	"cheats - easy money"
	if left() && var_b[2]==0 {
		if var_b[6] == 100 {
			var_c[0] = var_c[0] * 80 / 100;
		}
	}
	if right() && var_b[0]==0 {
		if var_b[6] == 100 {
			var_c[0] = var_c[0] * 125 / 100;
		}
	}
	if b_btn() && var_b[2]==0 {
		var_c[0] ++;
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


