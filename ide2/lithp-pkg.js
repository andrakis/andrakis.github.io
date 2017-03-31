(function e(t,n,r){function s(o,u){if(!n[o]){if(!t[o]){var a=typeof require=="function"&&require;if(!u&&a)return a(o,!0);if(i)return i(o,!0);var f=new Error("Cannot find module '"+o+"'");throw f.code="MODULE_NOT_FOUND",f}var l=n[o]={exports:{}};t[o][0].call(l.exports,function(e){var n=t[o][1][e];return s(n?n:e)},l,l.exports,e,t,n,r)}return n[o].exports}var i=typeof require=="function"&&require;for(var o=0;o<r.length;o++)s(r[o]);return s})({1:[function(require,module,exports){
// files.js, generated from genfiles.sh
var files = {};
files['modules/stdlib.ast'] = require('lithp/modules/stdlib.json');
files['modules/lists.ast'] = require('lithp/modules/lists.json');
files['modules/pivot.ast'] = require('lithp/modules/pivot.json');
files['modules/file.ast'] = require('lithp/modules/file.json');
files['modules/stream.ast'] = require('lithp/modules/stream.json');
files['modules/symbols.ast'] = require('lithp/modules/symbols.json');
files['modules/match.ast'] = require('lithp/modules/match.json');
files['modules/cache.ast'] = require('lithp/modules/cache.json');
files['modules/buffer.ast'] = require('lithp/modules/buffer.json');
files['modules/math.ast'] = require('lithp/modules/math.json');
files['modules/repl.ast'] = require('lithp/modules/repl.json');
files['modules/class.ast'] = require('lithp/modules/class.json');
files['modules/switch.ast'] = require('lithp/modules/switch.json');
files['modules/assert.ast'] = require('lithp/modules/assert.json');
files['modules/strings.ast'] = require('lithp/modules/strings.json');
files['modules/random.ast'] = require('lithp/modules/random.json');
files['modules/stderr.ast'] = require('lithp/modules/stderr.json');
files['modules/bignum.ast'] = require('lithp/modules/bignum.json');
files['modules/readline.ast'] = require('lithp/modules/readline.json');
files['samples/pillow.ast'] = require('lithp/samples/pillow.json');
files['samples/readfile.ast'] = require('lithp/samples/readfile.json');
files['samples/complex.ast'] = require('lithp/samples/complex.json');
files['samples/module.ast'] = require('lithp/samples/module.json');
files['samples/simple.ast'] = require('lithp/samples/simple.json');
files['samples/fib.ast'] = require('lithp/samples/fib.json');
files['samples/n-circles.ast'] = require('lithp/samples/n-circles.json');
files['samples/one_to_ten.ast'] = require('lithp/samples/one_to_ten.json');
files['samples/factorial.ast'] = require('lithp/samples/factorial.json');
files['samples/progruzzle-colf.ast'] = require('lithp/samples/progruzzle-colf.json');
files['samples/interlace-strings.ast'] = require('lithp/samples/interlace-strings.json');
files['samples/pairable.ast'] = require('lithp/samples/pairable.json');
files['samples/square.ast'] = require('lithp/samples/square.json');
files['samples/module_lib.ast'] = require('lithp/samples/module_lib.json');
files['samples/var_args.ast'] = require('lithp/samples/var_args.json');
files['samples/inverse.ast'] = require('lithp/samples/inverse.json');
files['samples/aspect.ast'] = require('lithp/samples/aspect.json');
files['samples/subchains.ast'] = require('lithp/samples/subchains.json');
files['samples/calc.ast'] = require('lithp/samples/calc.json');
files['samples/integral.ast'] = require('lithp/samples/integral.json');
files['samples/oddword.ast'] = require('lithp/samples/oddword.json');
files['samples/eval.ast'] = require('lithp/samples/eval.json');
files['samples/bfib.ast'] = require('lithp/samples/bfib.json');
files['samples/atoms.ast'] = require('lithp/samples/atoms.json');
files['samples/scope.ast'] = require('lithp/samples/scope.json');
files['samples/forloop.ast'] = require('lithp/samples/forloop.json');
files['samples/fndefs.ast'] = require('lithp/samples/fndefs.json');
files['samples/definitions.ast'] = require('lithp/samples/definitions.json');
files['samples/while.ast'] = require('lithp/samples/while.json');
files['samples/pow.ast'] = require('lithp/samples/pow.json');
files['samples/ext.ast'] = require('lithp/samples/ext.json');
files['samples/md-template.ast'] = require('lithp/samples/md-template.json');
files['samples/map.ast'] = require('lithp/samples/map.json');
files['samples/recurse.ast'] = require('lithp/samples/recurse.json');
files['samples/shorthand.ast'] = require('lithp/samples/shorthand.json');
files['samples/wall.ast'] = require('lithp/samples/wall.json');
files['modules/jquery-toolkit.ast'] = require('./modules/jquery-toolkit.json');
files['modules/html-toolkit.ast'] = require('./modules/html-toolkit.json');
files['modules/html.ast'] = require('./modules/html.json');
files['webide/palette.ast'] = require('./webide/palette.json');
files['webide/webide.ast'] = require('./webide/webide.json');
module.exports = files;


},{"./modules/html-toolkit.json":3,"./modules/html.json":5,"./modules/jquery-toolkit.json":7,"./webide/palette.json":139,"./webide/webide.json":141,"lithp/modules/assert.json":18,"lithp/modules/bignum.json":20,"lithp/modules/buffer.json":22,"lithp/modules/cache.json":24,"lithp/modules/class.json":26,"lithp/modules/file.json":28,"lithp/modules/lists.json":30,"lithp/modules/match.json":32,"lithp/modules/math.json":34,"lithp/modules/pivot.json":36,"lithp/modules/random.json":38,"lithp/modules/readline.json":40,"lithp/modules/repl.json":42,"lithp/modules/stderr.json":44,"lithp/modules/stdlib.json":46,"lithp/modules/stream.json":48,"lithp/modules/strings.json":50,"lithp/modules/switch.json":52,"lithp/modules/symbols.json":54,"lithp/samples/aspect.json":61,"lithp/samples/atoms.json":63,"lithp/samples/bfib.json":65,"lithp/samples/calc.json":67,"lithp/samples/complex.json":69,"lithp/samples/definitions.json":71,"lithp/samples/eval.json":73,"lithp/samples/ext.json":75,"lithp/samples/factorial.json":77,"lithp/samples/fib.json":79,"lithp/samples/fndefs.json":81,"lithp/samples/forloop.json":83,"lithp/samples/integral.json":85,"lithp/samples/interlace-strings.json":87,"lithp/samples/inverse.json":89,"lithp/samples/map.json":91,"lithp/samples/md-template.json":93,"lithp/samples/module.json":95,"lithp/samples/module_lib.json":97,"lithp/samples/n-circles.json":99,"lithp/samples/oddword.json":101,"lithp/samples/one_to_ten.json":103,"lithp/samples/pairable.json":105,"lithp/samples/pillow.json":107,"lithp/samples/pow.json":109,"lithp/samples/progruzzle-colf.json":111,"lithp/samples/readfile.json":113,"lithp/samples/recurse.json":115,"lithp/samples/scope.json":117,"lithp/samples/shorthand.json":119,"lithp/samples/simple.json":121,"lithp/samples/square.json":123,"lithp/samples/subchains.json":125,"lithp/samples/var_args.json":127,"lithp/samples/wall.json":129,"lithp/samples/while.json":131}],2:[function(require,module,exports){
(function (global){
if(typeof window === 'undefined')
	window = {};

if(window.global != global) {
	window.global = window;
	global = window;
}

var lithp = require('lithp');
window.Lithp = lithp;

var util = require('util');
window.util = util; // expose to HTML pages

var files, samples;
try {
	files = require('./files');
	samples = require('./samples');
} catch (e) {
	console.error("Please run genfiles.sh");
	return;
}

//window.Lithp.set_debug_flag(true);

var instance = new lithp.Lithp();
window.lithpInstance = instance;
var code = files["webide/webide.ast"];
if(code === undefined)
	console.log("Error: webide not found");

if(global._lithp === undefined)
	global._lithp = {};
global._lithp.browserify = true;
global._lithp.fileCache = files;
global._lithp.fileSampleCache = samples;

var ideParsed = lithp.Parser(code, {ast: true, finalize: true});
instance.setupDefinitions(ideParsed, "webide.ast")
instance.Define(ideParsed, "__AST__", lithp.Types.Atom('true'));
instance.Define(ideParsed, "RUNTIME", "browser");
global._lithp.host = "browser";
instance.run(ideParsed);

window.onload = function() {
	if(instance.Defined(ideParsed, "HTML_TOOLKIT") == lithp.Types.Atom('true')) {
		console.log("Invoking onReady behaviour");
		try {
			instance.Invoke(ideParsed, "onReady/*", [document, window]);
		} catch (e) {
			console.log(e.stack);
		}
	}
	if(window.jQuery && instance.Defined(ideParsed, "JQUERY_TOOLKIT") == lithp.Types.Atom('true')) {
		console.log("Invoking jQuery behaviour");
		window.jQuery.noConflict();
		try {
			instance.Invoke(ideParsed, "onJQuery/1", [window.jQuery])
		} catch (e) {
			console.log(e.stack);
		}
	}
};

}).call(this,typeof global !== "undefined" ? global : typeof self !== "undefined" ? self : typeof window !== "undefined" ? window : {})
},{"./files":1,"./samples":138,"lithp":10,"util":137}],3:[function(require,module,exports){
module.exports=[[["define","'HTML_TOOLKIT'","true"],["import","lists"],["var","Document",["atom","nil"]],["var","Window",["atom","nil"]],["var","HtmlToolkitOnReady",["list"]],["var","Ready","false"],["def","onReady/*",["scope",{"code":[[["set","Document",["index","Values","0"]],["set","Window",["index","Values","1"]],["set","Ready","true"],["each","HtmlToolkitOnReady",{"code":[[["call","Callback"]]],"_fndef":true,"_fnparams":["Callback"]}]]],"_fndef":true,"_fnparams":["Values"]}]],["export-global","onReady/*"],["def","htmlOnLoad",["scope",{"code":[[["if",["==","false","Ready"],[["set","HtmlToolkitOnReady",["++","HtmlToolkitOnReady",["list","Callback"]]]],["else",[["call","Callback"]]]],["atom","ok"]]],"_fndef":true,"_fnparams":["Callback"]}]],["export-global","htmlOnLoad/1"],["def","getElementById",["scope",{"code":[[["doc-apply","getElementById",["list","Id"]]]],"_fndef":true,"_fnparams":["Id"]}]],["def","prompt",["scope",{"code":[[["var","Result",["invoke","Window","prompt","Question"]],["call","Callback","Result"]]],"_fndef":true,"_fnparams":["Question","Callback"]}]],["export-global","prompt/2"],["def","doc-apply",["scope",{"code":[[["js-apply","Document",["dict-get","Document","Member"],"Args"]]],"_fndef":true,"_fnparams":["Member","Args"]}]],["def","getDoc",["scope",{"code":[[["Document"]]],"_fndef":true,"_fnparams":[]}]],["export-global","getDoc/0"],["def","getWindow",["scope",{"code":[[["Window"]]],"_fndef":true,"_fnparams":[]}]],["export-global","getWindow/0"],["def","postParentMessage",{"code":[[["var","Window",["getWindow"]],["js-apply","Window",["dict-get","Window","\"LithpPostMessage\""],["list","Message"]]]],"_fndef":true,"_fnparams":["Message"]}],["export-global","postParentMessage/1"]]]
},{}],4:[function(require,module,exports){
module.exports = "% Provides a basic interface to HTML objects in the document.\n% You must invoke onReady/1 with the \"body\" element.\n(\n\t(define 'HTML_TOOLKIT' true)\n\t(import lists)\n\n\t(var Document (atom nil))\n\t(var Window   (atom nil))\n\t(var HtmlToolkitOnReady (list))\n\t(var Ready false)\n\t(def onReady/* (scope #Values :: (\n\t\t(set Document (index Values 0))\n\t\t(set Window   (index Values 1))\n\t\t(set Ready true)\n\t\t(each HtmlToolkitOnReady #Callback :: (\n\t\t\t(call Callback)\n\t\t))\n\t)))\n\n\t(export-global onReady/*)\n\n\t(def htmlOnLoad (scope #Callback :: (\n\t\t(if (== false Ready) (\n\t\t\t(set HtmlToolkitOnReady (++\n\t\t\t\t HtmlToolkitOnReady (list Callback)\n\t\t\t))\n\t\t) (else (\n\t\t\t(call Callback)\n\t\t)))\n\t\t(atom ok)\n\t)))\n\n\t(export-global htmlOnLoad/1)\n\n\t(def getElementById (scope #Id :: (\n\t\t(doc-apply getElementById (list Id))\n\t)))\n\n\t(def prompt (scope #Question,Callback :: (\n\t\t(var Result (invoke Window prompt Question))\n\t\t(call Callback Result)\n\t)))\n\n\t(export-global prompt/2)\n\n\t(def doc-apply (scope #Member,Args :: (\n\t\t(js-apply Document (dict-get Document Member) Args)\n\t)))\n\n\t(def getDoc (scope # :: ((Document))))\n\t(export-global getDoc/0)\n\n\t(def getWindow (scope # :: ((Window))))\n\t(export-global getWindow/0)\n\n\t(def postParentMessage #Message :: (\n\t\t(var Window (getWindow))\n\t\t(js-apply Window (dict-get Window \"LithpPostMessage\") (list Message))\n\t))\n\t(export-global postParentMessage/1)\n)\n";

},{}],5:[function(require,module,exports){
module.exports=[[["atom","test"]]]
},{}],6:[function(require,module,exports){
module.exports = "(\n\t(atom test)\n)\n";

},{}],7:[function(require,module,exports){
module.exports=[[["import","lists"],["import","class"],["define","'JQUERY_TOOLKIT'","true"],["var","JQueryJSObj",["atom","nil"]],["var","JQueryOnLoadCallbacks",["list"]],["def","onJQuery",["scope",{"code":[[["set","JQueryJSObj",["get","JQ"]],["each","JQueryOnLoadCallbacks",{"code":[[["call","CB"]]],"_fndef":true,"_fnparams":["CB"]}]]],"_fndef":true,"_fnparams":["JQ"]}]],["def","jqueryOnLoad",["scope",{"code":[[["set","JQueryOnLoadCallbacks",["++","JQueryOnLoadCallbacks",["list","Callback"]]],["atom","ok"]]],"_fndef":true,"_fnparams":["Callback"]}]],["export-global","onJQuery/1","jqueryOnLoad/1"],["def","jQuery/1",{"code":[[["jQueryClass",["jquery-init","Selector"]]]],"_fndef":true,"_fnparams":["Selector"]}],["def","jQuery/2",{"code":[[["jQueryClass",["jquery-init","Selector",["unclass","Context"]]]]],"_fndef":true,"_fnparams":["Selector","Context"]}],["def","jQuery/3",{"code":[[["jQueryClass",["jquery-init","Selector",["unclass","Context"],"Root"]]]],"_fndef":true,"_fnparams":["Selector","Context","Root"]}],["export-global","jQuery/1","jQuery/2","jQuery/3"],["def","jquery-init/*",{"code":[[["js-invoke","JQueryJSObj","Args"]]],"_fndef":true,"_fnparams":["Args"]}],["def","jQueryClass",{"code":[[["new","JQueryClass","JQueryResult"]]],"_fndef":true,"_fnparams":["JQueryResult"]}],["def","unclass",{"code":[[["if",["==","dict",["typeof","JQ"]],[["member-call","JQ","getTarget"]],["else",[["JQ"]]]]]],"_fndef":true,"_fnparams":["JQ"]}],["var","JQueryClass",["class","'JQueryClass'",["tuple",["class-init"],{"code":[[["member-set","Self","target","From"]]],"_fndef":true,"_fnparams":["Self","From"]}],["tuple","append",{"code":[[["member-call","Self","call","append",["list",["unclass","Obj"]]]]],"_fndef":true,"_fnparams":["Self","Obj"]}],["tuple","bind",{"code":[[["member-call","Self","call","bind",["list","Event",["js-bridge","Handler"]]]]],"_fndef":true,"_fnparams":["Self","Event","Handler"]}],["tuple","getCss",{"code":[[["member-call","Self","invoke","css",["list"]]]],"_fndef":true,"_fnparams":["Self"]}],["tuple","getValue",{"code":[[["member-call","Self","invoke","val",["list"]]]],"_fndef":true,"_fnparams":["Self"]}],["tuple","remove",{"code":[[["member-call","Self","call","remove",["list"]]]],"_fndef":true,"_fnparams":["Self"]}],["tuple","setCss",{"code":[[["member-call","Self","call","css",["list","Css"]]]],"_fndef":true,"_fnparams":["Self","Css"]}],["tuple","setValue",{"code":[[["member-call","Self","call","val",["list","Value"]]]],"_fndef":true,"_fnparams":["Self","Value"]}],["tuple","call",{"code":[[["new","JQueryClass",["member-call","Self","invoke","Member","Args"]]]],"_fndef":true,"_fnparams":["Self","Member","Args"]}],["tuple","invoke",{"code":[[["js-apply",["member-get","Self","target"],["member-call","Self","getTargetMember","Member"],"Args"]]],"_fndef":true,"_fnparams":["Self","Member","Args"]}],["tuple","invoke-immediate",{"code":[[["invoke",["member-get","Self","target"],["list","Search"]]]],"_fndef":true,"_fnparams":["Self","Search"]}],["tuple","getTarget",{"code":[[["member-get","Self","target"]]],"_fndef":true,"_fnparams":["Self"]}],["tuple","getTargetMember",{"code":[[["dict-get",["member-call","Self","getTarget"],"Member"]]],"_fndef":true,"_fnparams":["Self","Member"]}]]]]]
},{}],8:[function(require,module,exports){
module.exports = "% Provides an interface to the jQuery object.\n(\n\t(import lists)\n\t(import class)\n\n\t(define 'JQUERY_TOOLKIT' true)\n\n\t(var JQueryJSObj (atom nil))\n\t(var JQueryOnLoadCallbacks (list))\n\n\t% Called by the JavaScript editor when code is run\n\t(def onJQuery (scope #JQ :: (\n\t\t(set JQueryJSObj (get JQ))\n\t\t(each JQueryOnLoadCallbacks #CB :: (\n\t\t\t(call CB)\n\t\t))\n\t)))\n\n\t% Used to add a callback when the above function is called.\n\t% Essentially, this is your $(function() { }) callback.\n\t(def jqueryOnLoad (scope #Callback :: (\n\t\t(set JQueryOnLoadCallbacks (++ JQueryOnLoadCallbacks (list Callback)))\n\t\t(atom ok)\n\t)))\n\n\t(export-global onJQuery/1 jqueryOnLoad/1)\n\n\t% Public API\n\t(def jQuery/1 #Selector :: (\n\t\t(jQueryClass (jquery-init Selector))\n\t))\n\t(def jQuery/2 #Selector,Context :: (\n\t\t(jQueryClass (jquery-init Selector (unclass Context)))\n\t))\n\t(def jQuery/3 #Selector,Context,Root :: (\n\t\t(jQueryClass (jquery-init Selector (unclass Context) Root))\n\t))\n\n\t(export-global jQuery/1 jQuery/2 jQuery/3)\n\n\t% Internal API\n\t(def jquery-init/* #Args :: (\n\t\t(js-invoke JQueryJSObj Args)\n\t))\n\n\t(def jQueryClass #JQueryResult :: (\n\t\t(new JQueryClass JQueryResult)\n\t))\n\n\t% Grabs the jQuery object from the class, if it is a class.\n\t(def unclass #JQ :: (\n\t\t(if (== dict (typeof JQ)) (\n\t\t\t(member-call JQ getTarget)\n\t\t) (else ((JQ))))\n\t))\n\n\t% The JQuery class\n\t(var JQueryClass (class 'JQueryClass'\n\t\t(tuple (class-init) #Self,From :: (\n\t\t\t(member-set Self target From)\n\t\t))\n\n\t\t% Public API\n\t\t(tuple append #Self,Obj :: (\n\t\t    (member-call Self call append (list (unclass Obj)))\n\t\t))\n\t\t(tuple bind #Self,Event,Handler :: (\n\t\t\t(member-call Self call bind (list Event (js-bridge Handler)))\n\t\t))\n\t\t(tuple getCss #Self :: (\n\t\t\t(member-call Self invoke css (list))\n\t\t))\n\t\t(tuple getValue #Self :: (\n\t\t\t(member-call Self invoke val (list))\n\t\t))\n\t\t(tuple remove #Self :: (\n\t\t\t(member-call Self call remove (list))\n\t\t))\n\t\t(tuple setCss #Self,Css :: (\n\t\t\t(member-call Self call css (list Css))\n\t\t))\n\t\t(tuple setValue #Self,Value :: (\n\t\t\t(member-call Self call val (list Value))\n\t\t))\n\n\t\t% Internal use\n\t\t(tuple call #Self,Member,Args :: (\n\t\t\t(new JQueryClass (member-call Self invoke Member Args))\n\t\t))\n\t\t(tuple invoke #Self,Member,Args :: (\n\t\t\t(js-apply (member-get Self target) (member-call Self getTargetMember Member) Args)\n\t\t))\n\t\t(tuple invoke-immediate #Self,Search :: (\n\t\t\t(invoke (member-get Self target) (list Search))\n\t\t))\n\t\t(tuple getTarget #Self :: (\n\t\t\t(member-get Self target)\n\t\t))\n\t\t(tuple getTargetMember #Self,Member :: (\n\t\t\t(dict-get (member-call Self getTarget) Member)\n\t\t))\n\t))\n)\n";

},{}],9:[function(require,module,exports){

},{}],10:[function(require,module,exports){


/**
 * Provides the interface to Lithp to other modules.
 */

var lithp = require('./lib/lithp');
exports.Lithp = lithp.Lithp;
exports.debug = lithp.debug;
exports.get_debug_flag = lithp.get_debug_flag;
exports.set_debug_flag = lithp.set_debug_flag;
exports.Types = require('./lib/types');
exports.Parser = require('./platform/v0/parser').BootstrapParser;

},{"./lib/lithp":13,"./lib/types":14,"./platform/v0/parser":57}],11:[function(require,module,exports){
(function (process,global){
/**
 * Builtin Lithp runtime library.
 *
 * Contains a number of critical utility functions such as control flow,
 * function definition, arithmatic, and some basic IO.
 */

"use strict";

var util = require('util'),
    inspect = util.inspect,
	path = require('path'),
	fs = require('fs');
var types = require('./types'),
	Atom = types.Atom,
	Tuple = types.Tuple,
	OpChain = types.OpChain,
	FunctionCall = types.FunctionCall,
	FunctionDefinition = types.FunctionDefinition,
	FunctionDefinitionNative = types.FunctionDefinitionNative,
	VariableReference = types.VariableReference,
	LiteralValue = types.LiteralValue;

// Note: import/1 currently uses the Bootstrap parser, Platform V0.
var BootstrapParser = require('../platform/v0/parser').BootstrapParser;

var builtins = {};

// Cache these frequently used atoms
var atomTrue   = Atom('true'),
    atomFalse  = Atom('false'),
    atomNil    = Atom('nil'),
    atomMissing= Atom('missing'),
    atomNumber = Atom('number'),
    atomString = Atom('string'),
    atomList   = Atom('list'),
    atomOpChain= Atom('opchain'),
    atomFunction=Atom('function'),
    atomTuple  = Atom('tuple'),
    atomAtom   = Atom('atom'),
    atomDict   = Atom('dict'),
    atomObject = Atom('object');

function builtin (name, params, body) {
	builtins[name] = {params: params, body: body};
}

builtin('def', ['Name', 'Body'], function(Name, Body, State) {
	//console.log("def/2", arguments);
	if(Name.type != 'Atom')
		throw new Error('Expected atom for function name in def/2, got: ' + inspect(Name.constructor));
	if(Body.constructor !== FunctionDefinition)
		throw new Error('Expected FunctionDefinition in def/2, got: ' + inspect(Body.constructor));

	var realName = Name.name;
	// No arity given, detect it and adjust name
	var arityIndex = realName.indexOf("/");
	if(arityIndex == -1) {
		// Adjust Name to include arity
		realName += '/' + Body.fn_params.length;
	} else {
		// Arity given, update Body arity to given count
		Body.arity = realName.slice(arityIndex + 1);
		//console.log("Setting aritity to given: " + Body.arity);
	}
	//console.log("Setting " + realName + " to ", Body);
	Body.readable_name = Name.name;
	State.closure.set_immediate(realName, Body);
	return Body;
});
builtin('==', ['X', 'Y'], (X, Y) => (X == Y) ? atomTrue : atomFalse);
builtin('!=', ['X', 'Y'], (X, Y) => (X != Y) ? atomTrue : atomFalse);
builtin('>',  ['X', 'Y'], (X, Y) => (X  > Y) ? atomTrue : atomFalse);
builtin('>=', ['X', 'Y'], (X, Y) => (X >= Y) ? atomTrue : atomFalse);
builtin('<',  ['X', 'Y'], (X, Y) => (X  < Y) ? atomTrue : atomFalse);
builtin('<=', ['X', 'Y'], (X, Y) => (X <= Y) ? atomTrue : atomFalse);
builtin('!',  ['X'], (X) => {
	if(X !== undefined) {
		if(X == atomTrue)
			return atomFalse;
		else if(X == atomFalse)
			return atomTrue;
		else
			throw new Error('Unable to evaulate !Atom(' + X.name + ')');
	}
	return !X;
});
builtin('and/*', [], (Args) => {
	var val = true;
	var arg;
	if(Args.length == 0)
		return atomFalse;
	var it = Args.iterator();
	it.rewind();
	while(val == true && (arg = it.next())) {
		val = (arg == atomTrue);
	}
	if(val == true)
		return atomTrue;
	else
		return atomFalse;
});
builtin('or/*', [], (Args) => {
	var val = false;
	var arg;
	if(Args.length == 0)
		return atomFalse;
	var it = Args.iterator();
	it.rewind();
	while((arg = it.next())) {
		val = (arg == atomTrue) || val;
	}
	if(val == true)
		return atomTrue;
	else
		return atomFalse;
});

// Add two or more lists together.
// Throws error if no lists given.
// Returns first given list if length is 1.
builtin('++/*', [], List => {
	if(List.length == 0)
		throw new Error('++/* requires at least one list');
	var it = List.iterator();
	var value = it.next();
	var n;
	while((n = it.next()) !== undefined) {
		value = value.concat(n);
	}
	return value;
});
// Add items together. Uses JavaScript + operator, so supports many different
// types of objects.
builtin('+/*', [], List => {
	if(List.length == 0)
		return 0; // TODO: Not appropriate for strings
	var it = List.iterator();
	var value = it.next();
	var n;
	while((n = it.next()) !== undefined) {
		value += n;
	}
	return value;
});
builtin('-/*', [], List => {
	if(List.length == 0)
		return 0;
	var it = List.iterator();
	var value = it.next();
	var n;
	if(List.length == 1)
		return -value;
	while((n = it.next()) !== undefined) {
		value -= n;
	}
	return value;
});
builtin('*/*', [], List => {
	if(List.length == 0)
		return 0;
	var it = List.iterator();
	var value = it.next();
	var n;
	while((n = it.next()) !== undefined) {
		value *= n;
	}
	return value;
});
builtin('//*', [], List => {
	if(List.length == 0)
		return 0;
	var it = List.iterator();
	var value = it.next();
	var n;
	while((n = it.next()) !== undefined) {
		value /= n;
	}
	return value;
});
// Difference between ?/3 and if/3 is that if/3 will evaluate
// the opchain given as the parameters. ?/3 simply returns the
// values as they are (ie, you cannot use an OpChain, unless you
// simply want to work with it.)
builtin('?', ['Pred', 'X', 'Y'], (Pred, X, Y) => (Pred == atomTrue) ? X : Y);
// Alias to if/3
builtin('if/2', ['Test', 'Action'], (Test, Action, State) =>
	builtins['if/3'].body.call(this, Test, Action, new OpChain(State), State)
);
function getIfResult (value) {
	if(value && value.constructor == OpChain)
		return value.call_immediate();
	else
		return value;
}
builtin('if/3', ['Test', 'Action', 'Else'], (Test, Action, Else) =>
	getIfResult((Test == atomTrue) ? Action : Else)
);
builtin('while/2', ['Test', 'Action'], function (Test, Action, State) {
	Test.parent = State;
	Test.closure.parent = State.closure;
	Action.parent = State;
	Action.closure.parent = State.closure;
	Test.rewind();
	Action.rewind();
	while(this.run(Test) == atomTrue) {
		Test.rewind();
		Action.rewind();
		this.run(Action);
	}
});
// Simply run chain
builtin('else', ['Chain'], (Chain) => Chain.call_immediate());
builtin('set', ['Name', 'Value'], (Name, Value, State) => {
	if(Name.constructor === VariableReference)
		Name = Name.ref;
	//console.log("(set/2: setting " + inspect(Name) + " to ", Value, ")");
	State.closure.set(Name, Value);
	return Value;
});
builtin('get', ['Name'], (Name, State) => {
	if(Name.constructor === VariableReference)
		Name = Name.ref;
	if(Name.type == 'Atom')
		Name = Name.name;
	var value = State.closure.get_or_missing(Name);
	if(value == atomMissing) {
		if(!State.closure.any_defined(Name)) {
			//console.log("ERROR: Available symbols: ", State.closure.closure);
			//console.log("Parent:", State.closure.parent);
			throw new Error('No symbol defined as ' + Name);
		}
	}
	return value;
});

// Set a variable in the local scope
builtin('var', ['Name', 'Value'], (Name, Value, State) => {
	if(Name.constructor === VariableReference)
		Name = Name.ref;
	//console.log("(set/2: setting " + inspect(Name) + " to ", Value, ")");
	State.closure.set_immediate(Name, Value);
	return Value;
});

builtin('print/*', [], function(Args) {
	// Print out all Args after inspecting
	console.log.apply(console, Args.map(O => {
		if(typeof O == "string")
			return O;
		return this.inspect_object([O], undefined, 0);
	}));
	return atomNil;
});

builtin('list/*', [], Args => Args);

builtin('map', ['List', 'Callback'], function(List, Callback, State) {
	return List.map(I => {
		return this.invoke_functioncall(State, Callback, [I]);
	});
});

builtin('slice/1', ['List'], List => List.slice());
builtin('slice/2', ['List', 'Begin'], (List, Begin) => List.slice(Begin));
builtin('slice/3', ['List', 'Begin', 'End'], (List, Begin, End) => List.slice(Begin, End));
builtin('quote/1', ['String'], S => JSON.stringify(S));
builtin('inspect/1', ['Object'], function(O) { return this.inspect_object([O], undefined, 0); });
builtin('inspect/2', ['Object', 'FullDepth'], (O, Full) =>
	inspect(O, Full == atomTrue ? {depth:null} : {}));
builtin('null', [], () => null);
builtin('undefined', [], () => undefined);
builtin('@', ['A', 'B'], (A, B) => A % B);
builtin('&', ['A', 'B'], (A, B) => A & B);
builtin('|', ['A', 'B'], (A, B) => A | B);
builtin('^', ['A', 'B'], (A, B) => A ^ B);
builtin('~', ['A'], A => ~A);
builtin('<<', ['A', 'B'], (A, B) => (A << B) >>> 0);
builtin('<<<', ['A', 'B'], (A, B) => A << B);
builtin('>>', ['A', 'B'], (A, B) => (A >> B) >>> 0);
builtin('>>>', ['A', 'B'], (A, B) => A >> B);
builtin('nl', [], () => String.fromCharCode(10)); // new line

builtin("match", ['String', 'RegexString'], (Str, RegexString) => Str.match(RegexString));
builtin("replace", ['String', 'RegexString', 'ReplaceStringOrFunction'], (Str, RegexString, ReplaceString) =>
	Str.replace(RegexString, ReplaceString)
);
builtin("test", ['Regex', 'String'], (Regex, Str) => Regex.test(Str));

builtin("regex/1", ["Regex"], (Regex) => new RegExp(Regex));
builtin("regex/2", ["Regex", "Flags"], (Regex, Flags) => new RegExp(Regex, Flags));
builtin("split", ['String', 'SplitChars'], (Str, SplitChars) => Str.split(SplitChars));
builtin("repeat", ['String', 'Count'], (Str, Count) => Str.repeat(Count));
builtin("join", ['List', 'JoinChar'], (List, JoinChar) => List.join(JoinChar));

builtin("head", ['List'], List => List.length > 0 ? List[0] : []);
builtin("tail", ['List'], List => List.length > 0 ? List.slice(1) : []);

builtin("ht", ['List'], List =>
	List.length == 0 ? [] : [List[0], List.slice(1)]
);

builtin("index", ['List', 'Index'], (List, Index) => List[Index]);

builtin("length", ['List'], List => List.length);

builtin("rand/0", [], () => Math.random());
builtin("rand/1", ['Start'], Start => Math.random(Start));
builtin("rand/2", ['Start', 'End'], (Start, End) => Math.random(Start, End));

builtin("exit/0", [], () => process.exit());
builtin("exit/1", ['Code'], Code => process.exit(Code));
builtin("env", [], () => process.env);
builtin("argv", [], () => process.argv);
builtin("cwd", [], () => process.cwd);

builtin('is-finite', ['N'], N => isFinite(N));
builtin('is-nan', ['N'], N => isNaN(N));
builtin('nan', [], () => NaN);
builtin('parse-float', ['Str'], Str => parseFloat(Str));
builtin('parse-int/1', ['Str'], Str => parseInt(Str));
builtin('parse-int/2', ['Str', 'Radix'], (Str, Radix) => parseInt(Str, Radix));
builtin('typeof', ['V'], V => {
	if(V)
		switch(V.constructor) {
			case Number:
				return atomNumber;
			case String:
				return atomString;
			case Array:
				return atomList;
			case OpChain:
				return atomOpChain;
			case FunctionDefinition:
				return atomFunction;
			case LiteralValue:
				return inbuilt({} /* fake context */, 'typeof', [V.value]);
			case Tuple:
				return atomTuple;
			default:
				if(V.type == 'Atom')
					return atomAtom;
				else if(Array.isArray(V))
					return atomList;
				else if(V[LITHP_DICT])
					return atomDict;
				return atomObject;
		}
	return Atom(typeof V);
});
builtin('function-arity', ['Function'], function(Fun) {
	if(Fun && Fun.constructor === FunctionDefinition)
		return Fun.arity;
	throw new Error('Given object is not a function definition: ' + inspect(Fun));
});
builtin('trim', ['S'], S => S.trim());
builtin('floor', ['N'], N => Math.floor(N));
builtin('ceil', ['N'], N => Math.ceil(N));

// Non-recursive list flatten
function flatten (List) {
	var result = [];
	var nodes = List.slice();
	var node;

	if(!List.length)
		return result;
	
	node = nodes.pop();

	do {
		if(Array.isArray(node))
			nodes.push.apply(nodes, node);
		else
			result.push(node);
	} while (nodes.length && (node = nodes.pop()) !== undefined);

	result.reverse();

	return result;
}

builtin("flatten/*", [], List => flatten(List));

// Call a function. This can be a JavaScript function, or one of the standard
// Lithp FunctionDefinition or FunctionDefinitionNative classes.
builtin("call/*", [], function(Args, State) {
	// Create a new OpChain with the given function, set the closure
	// variables, and return it with .call_immediate so that it takes
	// effect straight away.
	var Fn = Args.slice(0, 1);
	var Params = Args.slice(1);
	if(Fn.length == 0)
		throw new Error('call/*: Unable to get function from args');
	Fn = Fn[0];

	var val;
	if(typeof Fn == 'function') {
		// TODO: Could also transform this into a FunctionDefinitionNative
		// Pass along (this) to native functoin.
		val = Fn.apply(this, Params);
	} else {
		if (Fn.type == 'Atom')
			Fn = Fn.name;
		if (typeof Fn == 'string') {
			var fndef = State.closure.get_or_missing(Fn);
			if(fndef == atomMissing) {
				fndef = State.closure.get_or_missing(Fn + "/*");
				if(fndef == atomMissing) {
					throw new Error("Failed to find target: " + Fn);
				}
				Fn = fndef;
			}
		}
		val = this.invoke_functioncall(State, Fn, Params);
	}
	//console.log("call/* result:", val);
	return val;
});

builtin("apply/*", [], function(Args, State) {
	var Fn = Args.slice(0, 1)[0];
	var Params = Args.slice(1)[0];
	return builtins["call/*"].body.call(this, [Fn].concat(Params), State);
});

builtin("scope", ['FnDef'], (FnDef, State) => {
	// TODO: This is somewhat ugly and is implemented in the interpreter.
	//       It would be nice if this did not require changes to the
	//       interpreter.
	try {
		var newFnDef = FnDef.clone();
		newFnDef.scoped = State;
		//console.log("Scope, new scope is:", State.closure.getDefined(3));
		return newFnDef;
	} catch (e) {
		console.error("Was given: ", FnDef);
		throw e;
	}
});

builtin('try', ['Call', 'Catch'], function(Call, Catch, State) {
	Call.parent = State;
	Call.closure.parent = State.closure;
	Call.rewind();
	try {
		// this refers to the running Lithp object
		var value = this.run(Call);
		return value;
	} catch (e) {
		// Set Exception in the closure to the exception value e
		return this.invoke_functioncall(State, Catch, [e]);
	}
});
builtin('catch', ['OpChain'], (OpChain) => {
	return OpChain;
});
builtin('throw', ['Message'], (Message) => {
	throw new Error(Message);
});

// String Format
builtin('to-string/*', ['Args'], Args => {
	var S = Args[0];
	return S.toString.apply(S, Args.slice(1));
});

var definitionDict = '__definition_dict';
function getTopLevel (Chain) { return Chain.closure.getTopOwner(); };
function getDefinitionDict (Chain) {
	var toplevel = getTopLevel(Chain);
	var dict;
	if(!toplevel.defined(definitionDict)) {
		dict = {};
		dict[definitionDict] = true;
		dict = toplevel.set_immediate(definitionDict, dict);
	} else {
		// Return value is Tuple {ok, Tuple { value, closure_value_is_in }}
		var result = toplevel.get(definitionDict);
		if(result && result[0] == 'ok') {
			dict = result[1];
		} else {
			throw new Error("Runtime error: failed to get definition dictionary.");
		}
	}
	if(!dict[definitionDict])
		throw new Error("Runtime error: definition dict not valid: ", dict);
	return dict;
}

builtin('define', ['Name', 'Value'], function(Name, Value, State) {
	var dict = getDefinitionDict.call(this, State);
	dict[Name] = Value;
	return Value;
});

builtin('undefine', ['Name'], function (Name, State) {
	var dict = getDefinitionDict.call(this, State);
	var old = dict[Name];
	delete dict[Name];
	return old;
});

builtin('defined', ['Name'], function (Name, State) {
	return Name in getDefinitionDict.call(this, State) ? atomTrue : atomFalse;
});

builtin('get-def', ['Name'], function (Name, State) {
	var dict = getDefinitionDict.call(this, State);
	if(!(Name in dict))
		return Atom('false');
	return dict[Name];
});

builtin('definitions', [], function (State) { return getDefinitionDict.call(this, State); });

builtin('platform', ['Name'], function (Name, State) {
	var count;
	if(Name && Name.type == 'Atom')
		Name = Name.name;
	switch(Name.toLowerCase()) {
		case "v1":
			count = (require('../platform/v1/parser-lib')).setup(this);
			this.debug("PlatformV1 library loaded " + count + " symbols");
			// Re-import new functions
			State.importClosure(this.functions);
			break;
		default:
			var fullPath = path.resolve(Name + "/index.js");
			if(fs.existsSync(fullPath)) {
				// Import an extension
				count = (require(fullPath)).setup(this);
				this.debug("Extension library " + Name + " loaded " + count + " symbols");
				State.importClosure(this.functions);
				break;
			}
			throw new Error("Error: Platform " + Name + " not known.");
			break;
	}
});

var export_destinations = [];
builtin('export/*', ['Names'], function (Names, State) {
	if(export_destinations.length == 0) {
		export_destinations = [[this, State]];
	}
	// Get current destination
	var destination = export_destinations[export_destinations.length - 1];
	var dest_lithp = destination[0];
	var dest_chain = destination[1];
	var top_chain  = dest_chain.getTopParent();
	var fndefs = exportFunctions.call(this, Names, State, top_chain);
	this.debug("Exporting: [" + Object.keys(fndefs).join(', ') + "] from Lithp[" + this.id + "] to Lithp[" + dest_lithp.id + "]");
	top_chain.importClosure(fndefs);
});

builtin('export-global/*', ['Names'], function (Names, State) {
	if(export_destinations.length == 0) {
		export_destinations = [[this, State]];
	}
	// Current destination only used in call to exportFunction
	var destination = export_destinations[export_destinations.length - 1];
	var dest_lithp = destination[0];
	var dest_chain = destination[1];
	var top_chain  = dest_chain.getTopParent();
	var fndefs = exportFunctions.call(this, Names, State, top_chain);
	// Export to all other Lithp instances
	var instances = global.get_lithp_instances();
	for(var id in instances) {
		dest_lithp = instances[id];
		dest_chain = instances[id].last_chain;
		top_chain  = dest_chain.getTopParent();
		this.debug("Exporting: [" + Object.keys(fndefs).join(', ') + "] from Lithp[" + this.id + "] to Lithp[" + dest_lithp.id + "]");
		top_chain.importClosure(fndefs);
	}
});

function exportFunctions (Names, State, top_chain) {
	this.debug("Exporting: [" + Names.map(N => N.toString()).join(', ') + ']');
	var dest = {};
	Names.map(Name => {
		var result = State.closure.get(Name.toString());
		if(result && result[0] == 'ok') {
			this.debug("Exporting " + Name + " from OpChain[" + State.id + "] to OpChain[" + top_chain.id + "]");
			var fndef_named_function = result[1];
			// Create a new FunctionDefinitionNative that calls this interpreter to
			// run the OpChain.
			// Note that 'this' still refers to the current interpreter.
			var instance = this;
			var fndef_bridge = new FunctionDefinitionNative(
				fndef_named_function.fn_name,
				fndef_named_function.fn_params,
				function() {
					// Remove State from given arguments
					var Params = Array.prototype.slice.call(arguments, 0, arguments.length - 1);
					var val = instance.invoke_functioncall(State, fndef_named_function, Params);
					//instance.debug(" imported function call result: " + val);
					return val;
				}
			);
			dest[Name] = fndef_bridge;
		} else {
			console.log("ERROR: Available symbols: ", State.closure.closure);
			throw new Error("Export: failed to find " + Name.toString() + " to export.");
		}
	});
	return dest;
}

function findModule (name, State) {
	var search_paths = this.Defined(State, "_module_search_path") || [];
	var it = search_paths.iterator();
	var extensions = [''];
	if(this.Defined(State, "__AST__") == atomTrue) {
		extensions.push('.ast');
	}
	extensions.push('.lithp');
	var ext_it = extensions.iterator();

	var search;
	var extension;

	this.debug(" Find module: " + name);

	it.rewind();
	while((search = it.next()) || search !== undefined) {
		ext_it.rewind();
		while((extension = ext_it.next()) || extension !== undefined) {
			var search_name = path.join(search, name + extension);
			this.debug("  Checking " + search_name);
			if(global._lithp.browserify) {
				if(search_name in global._lithp.fileCache)
					return search_name;
			} else {
				if(fs.existsSync(search_name) && fs.lstatSync(search_name).isFile()) {
					this.debug(" Using " + search_name);
					return search_name;
				}
			}
		}
	}

	return name;
}

builtin('import', ['Path'], function (Path, State) {
	var importTable = this.Defined(State, "_modules_imported");
	this.debug("Attempt to import: " + Path);
	Path = findModule.call(this, Path, State);
	if(Path in importTable) {
		this.debug("Skipping already imported module");
		return;
	}

	if(!global._lithp.browserify && !fs.existsSync(Path))
		throw new Error("import: could not find file " + Path);
	
	importTable.push(Path);
	var instance = this;
	var code;
	if(global._lithp.browserify)
		code = global._lithp.fileCache[Path];
	else
		code = fs.readFileSync(Path).toString();
	var opts = {
		finalize: true,
		ast: null != Path.match(/.ast$/)
	}
	var timed = timeCall("Parse code", () => BootstrapParser(code, opts));
	var parsed = timed[0];
	parsed.parent = State;
	parsed.closure.parent = State.closure;
	if(this.Defined(State, "__AST__") == atomTrue) {
		this.Define(parsed, "__AST__", atomTrue);
	}
	this.debug("  module parsed in " + timed[1] + "ms");
	timeCall("Run module", () => {
		export_destinations.push([this, State]);
		instance.run(parsed)
		export_destinations.pop();
	});
	this.debug("  module run and exported to current instance in " + timed[1] + "ms");
	return atomNil;
});

builtin('import-instance', ['Path'], function (Path, State) {
	this.debug("Attempt to import: " + Path);
	Path = findModule.call(this, Path, State);
	if(!fs.existsSync(Path))
		throw new Error("import: could not find file " + Path);
	
	// We use a new instance of Lithp to run the module.
	// This gives it its own completely private set of definitions and functions.
	// When export is called, it will fill the function table with functions that
	// are owned by a different Lithp instance that could be doing its own thing
	// on callbacks.
	var instance = new Lithp();
	var code = fs.readFileSync(Path).toString();
	var timed = timeCall("Parse code", () => BootstrapParser(code, Path));
	var result;
	var parsed = timed[0];
	this.debug("  module parsed in " + timed[1] + "ms");
	timeCall("Run module", () => {
		instance.setupDefinitions(parsed, Path);
		export_destinations.push([this, State]);
		instance.run(parsed)
		export_destinations.pop();
	});
	this.debug("  module run and exported to current instance in " + timed[1] + "ms");
	return result;
});

builtin('eval/1', ['Code'], function(Code, State) {
	return builtins['eval/*'].body.call(this, [Code], State);
});
builtin("eval/*", ['CodeAndParams'], function(Args, State) {
	var code = Args.slice(0, 1)[0];
	var args = Args.slice(1);
	this.debug(" Parse: " + code);
	var compiled = BootstrapParser(code);
	//var instance = new Lithp();
	//this.setupDefinitions(compiled, "[evaluated code]");
	compiled.parent = State;
	compiled.closure.parent = State.closure;
	if(args.length > 0) {
		for(var i = 0; i < args.length; i++) {
			var arg = args[i];
			this.debug(" Defining " + arg[0] + " = ", arg[1]);
			compiled.closure.set_immediate(arg[0], arg[1]);
		}
	}
	return this.run(compiled);
});

builtin('atom', ['Name'], Name => Atom(Name));
// Invoke a JavaScript function using apply.
builtin('invoke/*', [], Args => {
	if(Args.length < 2)
		throw new Error("Invoke requires object and function name at least");
	var Obj = Args[0];
	var FnName = Args[1];
	var Params = Args.slice(2);
	if(!Obj[FnName])
		throw new Error("Invoke attempted, but " + FnName + " does not exist in: " + inspect(Obj));
	if(typeof Obj[FnName] != 'function')
		throw new Error("Invoke attempted, but " + FnName + " does not refer to a function: " + typeof(Obj[FnName]));
	return Obj[FnName].apply(Obj, Params);
});

builtin('abs', ['N'], N => Math.abs(N));
builtin('pi', [], () => Math.PI);
builtin('sqrt', ['N'], N => Math.sqrt(N));

builtin('chr', ['N'], N => String.fromCharCode(N));
builtin('asc', ['Str'], Str => Str.charCodeAt(0));

// Used to instantiate classes when the number of parameters it not
// known. Uses apply to instantiate (which is a little trickier than
// usual.)
function newClass (Cls) {
	// Function.bind.apply's first argument is ignored. Thus, it doesn't
	// matter that it's included in arguments.
	return new (Function.bind.apply(Cls, arguments));
}

builtin("tuple/*", [], function (List) {
	return newClass.apply(this, [Tuple].concat(List));
});

var LITHP_DICT = "__lithp_is_lithp_dict";
/** Members should be a list of tuples:
 *    {atom or string::Key, any::Value}
 */
builtin('dict/*', [], Members => {
	var Dict = {};
	Object.defineProperty(Dict, LITHP_DICT, {
		enumerable: false,
		writable: true
	});
	Dict[LITHP_DICT] = true;
	Object.defineProperty(Dict, LITHP_DICT, {
		writable: false
	});
	Members.forEach(Member => {
		if(Member.constructor === LiteralValue)
			Member = Member.value;
		if(Member.constructor !== Tuple) {
			throw new Error('dict expects a list of tuples, got' + inspect(Member));
		}
		if(Member.length != 2) {
			throw new Error('dict expects a tuple of {atom::Key, any::Value}');
		}
		var key = Member[0];
		var value = Member[1];
		if(key && key.type == 'Atom')
			key = key.name;
		Dict[key] = value;
	});
	return Dict;
});

// These functions can be used on JavaScript objects returned from require/1.
builtin('dict-get', ['Dict', 'Name'], (Dict, Name) => Dict[Name]);
builtin('dict-set', ['Dict', 'Name', 'Value'], (Dict, Name, Value) => {
	Dict[Name] = Value;
	return Dict;
});
builtin('dict-present', ['Dict', 'Name'], (Dict, Name) =>
	(Name in Dict) ? atomTrue : atomFalse
);
builtin('dict-remove', ['Dict', 'Name'], (Dict, Name) => {
	delete Dict[Name];
	return Dict;
});
builtin('dict-keys', ['Dict'], Dict => Object.keys(Dict));

// These are specific to JavaScript. This might matter in the future if the
// interpreter is ever ported, so they are prefixed.
builtin('require', ['Name'], Name => require(Name));
builtin('{}', [], () => {});
builtin('js-apply/3', ['Context', 'Function', 'ArgList'], (Ctx, F, AL) => {
	return F.apply(Ctx, AL);
});
builtin('js-typeof/1', ['Object'], O => typeof(O));
// Bridge to a JavaScript function. This returns a native JavaScript function
// that when called, invokes the given FunctionDefinition with the arguments
// given to the function. This can be used in fs.readFile for example.
builtin('js-bridge/1', ['FunctionDefinition'], function(FnDef, State) {
	return (self =>
		function() {
			var Args = Array.prototype.slice.call(arguments);
			return self.invoke_functioncall(State, FnDef, Args);
		}
	)(this);
});

builtin('true', [], () => true);
builtin('false', [], () => false);

builtin('add-search-path', ['Path'], function(Path, State) {
	var search = this.Defined(State, "_module_search_path");
	search.push(Path);
	return search;
});

builtin('host', [], () => global._lithp.host);
builtin('host-version', [], () => global._lithp.version);

builtin('stdin', [], () => process.stdin);
builtin('stdout', [], () => process.stdout);
builtin('stderr', [], () => process.stderr);

builtin('set-top-level', ['Bool'], Bool => global._lithp.set_toplevel = (Bool === Atom('true')));

builtin('index-set', ['List', 'Index', 'Value'], (List, Index, Value) => {
	List[Index] = Value;
	return List;
});

builtin('list-fill', ['Length', 'Value'], (Length, Value) => new Array(Length).fill(Value));
builtin('list-rand', ['List'], List => List[Math.floor(Math.random() * List.length)]);

builtin('recurse/*', ['Args'], function(Params, State) {
	// Find current target
	var Target = State.parent;
	while(Target && !Target.function_entry) {
		Target = Target.parent;
	}
	if(Target == null) {
		throw new Error('Failed to find current entry to ' + Fn);
	}
	// Rewind it to the start
	Target.rewind();

	// Get the OpChain function name with arity.
	var Fn = Target.function_entry;
	var FnAndArity = Fn + "/" + Params.length;
	var fndef = Target.closure.get_or_missing(FnAndArity);

	if(fndef == atomMissing) {
		// Check for a function with any arity assigned (*)
		FnAndArity = FnAndArity.replace(/\d+$/, '*');
		fndef = Target.closure.get_or_missing(FnAndArity);
		if(fndef == atomMissing) {
			throw new Error('Error, unknown function: ' + Fn + "/" + Params.length);
		}
	}

	// Set parameters for given function
	fndef.fn_params.forEach((Name, Index) => {
		//lithp_debug("Set '" + Name + "' to params[" + Index + "] (" + params[Index] + ")");
		// This ensures that the closure will immediately find
		// the named variable, instead of going up the stack
		// to find it (which might hold multiple variables of
		// the same name.)
		Target.closure.set_immediate(Name, Params[Index]);
	});

	// We return nothing. It's up to the given function to eventually stop recursion
	// and return a value.
});

function inbuilt (self, name, args, State) {
	return builtins[name].body.apply(self, args);
}

builtin('recurse-from/*', ['Args'], function(Args, State) {
	var From = inbuilt(this, 'head', [Args]);
	var Tail = inbuilt(this, 'tail', [Args]);
	var Fn   = inbuilt(this, 'head', [Tail]);
	var Params = inbuilt(this, 'tail', [Tail]);

	// Find target
	var Target = State.parent;
	while(Target && Target.function_entry != Fn) {
		Target = Target.parent;
	}
	if(Target == null) {
		throw new Error('Failed to find current entry to ' + Fn);
	}
	// Rewind it to the start
	Target.rewind();

	// Get the given function name with arity.
	var FnAndArity = Fn + "/" + Params.length;
	var fndef = Target.closure.get_or_missing(FnAndArity);

	if(fndef == atomMissing) {
		// Check for a function with any arity assigned (*)
		FnAndArity = FnAndArity.replace(/\d+$/, '*');
		fndef = Target.closure.get_or_missing(FnAndArity);
		if(fndef == atomMissing) {
			throw new Error('Error, unknown function: ' + Fn + "/" + Params.length);
		}
	}

	// Set parameters for given function
	fndef.fn_params.forEach((Name, Index) => {
		//lithp_debug("Set '" + Name + "' to params[" + Index + "] (" + params[Index] + ")");
		// This ensures that the closure will immediately find
		// the named variable, instead of going up the stack
		// to find it (which might hold multiple variables of
		// the same name.)
		Target.closure.set_immediate(Name, Params[Index]);
	});

	// We return nothing. It's up to the given function to eventually stop recursion
	// and return a value.
});

builtin('next/*', ['Args'], function(Args, State) {
	var Fn   = inbuilt(this, 'head', [Args]);
	var Params = inbuilt(this, 'tail', [Args]);

	// Find target - last function entry
	var Target = State.parent;
	while(Target && !Target.function_entry) {
		Target = Target.parent;
	}
	if(Target == null) {
		throw new Error('Failed to find last function entry');
	}

	// Get the given function name with arity.
	var FnAndArity = Fn + "/" + Params.length;
	var fndef = Target.closure.get_or_missing(FnAndArity);

	if(fndef == atomMissing) {
		// Check for a function with any arity assigned (*)
		FnAndArity = FnAndArity.replace(/\d+$/, '*');
		fndef = Target.closure.get_or_missing(FnAndArity);
		if(fndef == atomMissing) {
			throw new Error('Error, unknown function: ' + Fn + "/" + Params.length);
		}
	}

	Target.replaceWith(fndef);

	// Set parameters for given function
	fndef.fn_params.forEach((Name, Index) => {
		//lithp_debug("Set '" + Name + "' to params[" + Index + "] (" + params[Index] + ")");
		// This ensures that the closure will immediately find
		// the named variable, instead of going up the stack
		// to find it (which might hold multiple variables of
		// the same name.)
		Target.closure.set_immediate(Name, Params[Index]);
	});

	// We return nothing. It's up to the given function to eventually stop recursion
	// and return a value.
});

var lithp;
builtin('lithp-debug', ['Bool'], Bool =>
	lithp.set_debug_flag(Bool === Atom('true'))
);

// Moved to inbuilt function for speed reasons
builtin('flat-map', ['List', 'Callback'], function(List, Callback, State) {
	return Array.prototype.concat.apply([], List.map(E => this.invoke_functioncall(State, Callback, [E])));
});

builtin('opchain-rewind', ['OpChain'], (Chain) => {
	if(Chain && Chain.constructor == OpChain) {
		Chain.rewind();
		return atomNil;
	}
	throw new Error("Given value is not an opchain: " + Chain.constructor);
});

builtin('run', ['OpChain'], function(Chain) {
	if(Chain && Chain.constructor == OpChain) {
		Chain.rewind();
		return this.run(Chain);
	}
	throw new Error("Given value is not an opchain: " + Chain.constructor);
});

builtin('math-object', [], () => Math);

builtin('js-invoke', ['Fn', 'Args'], (Fn, Args) => {
	return Fn.apply(Fn, Args);
});

builtin('debugger', [], () => { debugger; });

var permutationsPossibilities = [0, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600];
builtin('permutations', ['List'], (List) => {
	var input = List.slice(); // duplicate
	var length = input.length;
	var result = new Array(permutationsPossibilities[length]).fill(0);
	var c = new Array(length).fill(0);
	var i = 1, j = 1;
	result[0] = input.slice();
	while(i < length) {
		if(c[i] < i) {
			var k = (i % 2) ? c[i] : 0,
			    p = input[i];
			input[i] = input[k];
			input[k] = p;
			++c[i];
			i = 1;
			result[j] = input.slice();
			j++;
		} else {
			c[i] = 0;
			i++;
		}
	}
	return result;
});

exports.setup = function(lithp) {
	for(var k in builtins) {
		lithp.builtin(k, builtins[k].params, builtins[k].body);
	}
};

// Lazy load
lithp = require('./..');

}).call(this,require('_process'),typeof global !== "undefined" ? global : typeof self !== "undefined" ? self : typeof window !== "undefined" ? window : {})
},{"../platform/v0/parser":57,"../platform/v1/parser-lib":59,"./..":10,"./types":14,"_process":134,"fs":9,"path":133,"util":137}],12:[function(require,module,exports){
(function (global){
/**
 * Lithp language interpreter.
 *
 * This is the main interpreter unit, and performs all the basic
 * interpreter functions.
 *
 * It operates only on prepared OpChains, requiring either hand-
 * compilation or a parser (see run.js.)
 *
 * See samples.js for some hand-compiled samples, or samples/ for files
 * that can be run with run.js
 *
 */

"use strict";

var util = require('util'),
	inspect = util.inspect;
var types = require('./types'),
	OpChain = types.OpChain,
	Atom = types.Atom,
	FunctionCall = types.FunctionCall,
	FunctionReentry = types.FunctionReentry,
	FunctionDefinition = types.FunctionDefinition,
	FunctionDefinitionNative = types.FunctionDefinitionNative,
	AnonymousFunction = types.AnonymousFunction,
	LiteralValue = types.LiteralValue,
	VariableReference = types.VariableReference,
	Tuple = types.Tuple;

var atomMissing = Atom('missing');

// This controls the maximum size of output for unknown objects being printed.
var maxDebugLen = 100;
var maxDebugArrayLength = 100;

/**
 * Run a function chain and return its value.
 * The is the top level interpreter, responsible for moving through
 * an OpChain and executing instructions, or just getting values
 * from LiteralValue returns.
 * This is the main function for running Lithp code.
 */
Lithp.prototype.run = function(chain) {
	if(this.stopped)
		throw new Error('Error: this instance has been stopped - ' + this.Defined(chain, '__filename'));
	this.last_chain = chain;
	// TODO: use a list for current OpChain to execute so that reduce can
	//       recall its function body
	var value = Atom("nil");
	//lithp_debug(chain);
	//lithp_debug("Resuming chain from pos: " + chain.pos);
	while(chain.next()) {
		var i = chain.get();
		switch(i.constructor) {
			case OpChain:
				//lithp_debug("(run: current closure: ", i.closure.closure);
				//lithp_debug("(      parent closure: ", i.closure.parent);
				value = this.run(new OpChain(chain, i.ops));
				break;
			case FunctionCall:
				//console.log("chain.get got: ", i);
				value = this._do_functioncall(chain, i);
				//lithp_debug("(run: got value from fn call: ", value);
				if(value && value.constructor === OpChain && value.immediate == true) {
					// Invoke this chain immediately
					//lithp_debug("(run: invoking immediately");
					value = this.run(new OpChain(chain, value.ops));
					//lithp_debug("(run: got value from immediate fn call: ", value);
				}
				break;
			case LiteralValue:
				value = i.value;
				break;
			case FunctionDefinition:
			case FunctionDefinitionNative:
				value = i;
				break;
			default:
				debug("ERROR: Unkown operation: " + i.constructor);
				break;
		}
	}
	//lithp_debug("Final value: " + value + " (" + ((value && value.type) ? value.type : typeof value) + ")");
	return value;
};

/**
 * Perform a function call with the given chain closure.
 *
 * This is the main interpreting function, it takes care
 * of creating new closures for a function call, making
 * the call itself, and finding the correct function to
 * call based on arity.
 *
 * For each argument, if it is a function call, this
 * procedure is called recursively, eventually returning
 * the appropriate real value so that the function call
 * can occur.
 */
Lithp.prototype._do_functioncall = function(chain, i) {
	//lithp_debug("FunctionCall " + i.fn_name + "(...)");
	var fn_name = i.fn_name;
	var fndef = chain.closure.topmost.get_or_missing(fn_name);
	if(fndef == atomMissing) {
		// Check local scope
		fndef = chain.closure.get_or_missing(fn_name);
		if(fndef == atomMissing) {
			// Check for a function with any arity assigned (*)
			fn_name = fn_name.replace(/\d+$/, '*');
			fndef = chain.closure.get_or_missing(fn_name);
			if(fndef == atomMissing) {
				throw new Error('Error, unknown function: ' + i.fn_name);
			}
			i.fn_name = fn_name; // Update reference for future
		}
	}
	// Get the real values of all parameters. This may recursively invoke
	// this function to satisfy calls.
	var self = this;
	var params = i.fn_params.map(function (P) {
		return self.get_param_value(chain, P);
	});
	//lithp_debug("Final params: ", inspect(params));
	//lithp_debug("Requesting invoke for: ", i);
	//lithp_debug("Found fndef: ", fndef);
	//lithp_debug("Actual fndef: ", fndef);
	return this.invoke_functioncall(chain, fndef, params);
};

/**
 * Get the real value of a parameter.
 * This converts LiteralValues into actual values, as well
 * as calling function calls or simply returning relevant data.
 */
Lithp.prototype.get_param_value = function (chain, param) {
	if(param === undefined)
		return undefined;
	// Atoms are passed whole
	if(param && param.type == 'Atom')
		return param;
	switch(param.constructor) {
		case FunctionCall: return this._do_functioncall(chain, param);
		case LiteralValue: return param.value;
		// The following just return the param itself.
		case VariableReference:
		case OpChain:
		case FunctionDefinition:
			return param;
		default:
			// debug("WARN: unknown value");
			// TODO: merge into above clause
			return param;
	}
};

// A special content parser for Lithp objects that attempts to have terse
// output. Will not output entire object if size is more than maxDebugLen.
function lithpInspectParser (P, Join, maxDebug) {
	maxDebug = (maxDebug === undefined) ? maxDebugLen : maxDebug;
	// Print strings using double quotes (inspect gives single.)
	// This is to differentiate it from atoms, which use single quotes.
	if(typeof P == typeof "")
		return (maxDebug <= 0 || (maxDebug > 0 && P.length <= maxDebug)) ?
			JSON.stringify(P) : '(string too large to display)';
	if(P)
		switch(P.constructor) {
			case OpChain:
			case VariableReference:
			case FunctionDefinition:
			case FunctionCall:
			case LiteralValue:
			case Tuple:
				return P.toString();
			default:
				if(P.type == 'Atom')
					return "'" + P.name + "'";
				else if(Array.isArray(P))
					if(P.length < maxDebugArrayLength)
						return '[' + P.map(function(V) { return lithpInspectParser(V, Join, maxDebug); }).join(Join) + ']';
					else
						return '[ ' + P.length + ' elements ]';
		}
	var val = inspect(P);
	if(val.length && maxDebug > 0 && val.length > maxDebug && P)
		val = "(" + (P.constructor.name || 'Object') + ": too large to display)";
	return val;
}

/**
 * Return a short string representation of the object.
 */
Lithp.prototype.inspect_object = function(Args, Join, maxDebugLen) {
	Join = Join || ' ';
	return Args.map(function(V) { return lithpInspectParser(V, Join, maxDebugLen); }).join(Join);
};

Lithp.prototype.Invoke = function(chain, fn_name, params) {
	var fndef = chain.closure.get_or_missing(fn_name);

	if(fndef == atomMissing) {
		// Check for a function with any arity assigned (*)
		fn_name = fn_name.replace(/\d+$/, '*');
		fndef = chain.closure.get_or_missing(fn_name);
		if(fndef == atomMissing) {
			throw new Error('Error, unknown function: ' + fn_name);
		}
	}

	return this.invoke_functioncall(chain, fndef, params);
};

/**
 * Invokes the given function with the given parameters. Assumes parameters
 * have all been resolved.
 *
 * This function can be used by builtin functions to call arbritrary functions.
 */
Lithp.prototype.invoke_functioncall = function(chain, fndef, params) {
	var debug_str = "";
	this.functioncalls++;
	if(global.lithp_debug_flag) {
		// Only call this in debug mode, since it involves mapping
		// over all of the parameters, which is just wasted time if
		// debug is not on.
		var lithp_id = global.get_lithp_max_id();
		var padding = (lithp_id.toString().length - this.id.toString().length);
		    padding = " ".repeat(padding);
		var fn_name = fndef.readable_name;
		if(fndef.constructor === FunctionDefinition)
			fn_name += "/" + fndef.arity;
		var indent = "|";
		if(this.depth < 20)
			indent = indent.repeat(this.depth + 1);
		else
			indent = "|             " + this.depth + " | | ";
		debug_str = (lithp_id > 1 ? "[" + padding + this.id + "] " : "") +
			"+ " + indent  + " (" + fndef.readable_name +
			(fndef.instance_id ? ':' + fndef.instance_id : '') +
			(params.length > 0 ? (" " + this.inspect_object(params, ' ')) : "") + ")";
	}
	var arity = fndef.arity;
	var val;
	this.depth++;
	if(fndef.constructor === FunctionDefinitionNative) {
		//lithp_debug("Calling FunctionDefinitionNative");
		// Call native JavaScript function. Passes given arguments
		// and also pass in the current chain as the last argument.
		if(global.lithp_debug_flag) {
			if(fndef.readable_name == 'while' || fndef.readable_name == 'call' ||
			   fndef.readable_name == 'try'   || fndef.readable_name == 'eval' ||
			   fndef.readable_name == 'apply' || fndef.readable_name == 'next' ||
			   fndef.readable_name == 'recurse')
				lithp_debug(debug_str);
		}
		if(arity == '*') {
			// For functions that have an arity of *, pass params as a single
			// argument.
			params = [params];
		}
		val = fndef.fn_body.apply(this, params.concat(chain));
		//lithp_debug("Value returned (native) : ", val);
	} else if (fndef.constructor === FunctionDefinition) {
		// Call a function. Creates a new OpChain from the given
		// function body, and sets the parameters of the closure
		// to the pushed values.
		lithp_debug(debug_str);
		// Set the correct scope. If the function definition has new one, use it.
		// TODO: This parent section is a bit of a hack. It would be nicer if
		//       it were implemented outside of the interpreter.
		var parent = chain;
		if(fndef.scoped)
			parent = fndef.scoped;
		var call_chain = new OpChain(parent, fndef.fn_body);
		if(arity == '*')
			params = [params];
		// Set args in new function closure
		fndef.fn_params.forEach((Name, Index) => {
			//lithp_debug("Set '" + Name + "' to params[" + Index + "] (" + params[Index] + ")");
			// This ensures that the closure will immediately find
			// the named variable, instead of going up the stack
			// to find it (which might hold multiple variables of
			// the same name.)
			call_chain.closure.set_immediate(Name, params[Index]);
		});
		//lithp_debug("Successfully set closure, definitions:", call_chain.closure.closure);
		//lithp_debug("             parent has A            :", call_chain.closure.get("A"));
		//lithp_debug("   Parent                            :", fndef.fn_body.parent);
		//lithp_debug("Invoking FunctionDefinition");
		// Mark it as a function entry
		call_chain.function_entry = fndef.readable_name;
		// Invoke the new chain
		val = this.run(call_chain);
		//lithp_debug("Value returned: ", val);
	} else {
		throw new Error("Don't know what to do with: " + inspect(fndef));
	}
	this.depth--;
	if(global.lithp_debug_flag) {
		debug_str += " :: " + this.inspect_object([val]);
		lithp_debug(debug_str);
	}
	return val;
};

}).call(this,typeof global !== "undefined" ? global : typeof self !== "undefined" ? self : typeof window !== "undefined" ? window : {})
},{"./types":14,"util":137}],13:[function(require,module,exports){
(function (process,global,__dirname){
/**
 * Lithp, a very small Lisp-like interpreter.
 *
 * This the parent module, and provides the basic interface to Lithp.
 * It includes exit handlers, debug flags, definitions, and basic chain
 * setup (once compiled.)
 */

"use strict";

var pjson = require('../package.json');

global._lithp = {};
global._lithp_start = new Date().getTime();
global._lithp_global_definitions = {};
global._lithp.set_toplevel = false;
global._lithp.version = pjson.version;
global._lithp.host = "Node.js";

global._LithpDefine = function(Name, Value) { global._lithp_global_definitions[Name] = Value; };

var util = require('util'),
	inspect = util.inspect,
	path = require('path');
require('./util');
var types = require('./types'),
	Atom = types.Atom,
	FunctionDefinitionNative = types.FunctionDefinitionNative;

var enable_debug = false;
function debug() {
	if(enable_debug)
		console.error.apply(console, arguments);
}
exports.debug = debug;
exports.get_debug_flag = function() { return enable_debug; };
exports.set_debug_flag = function(V) { return global.lithp_debug_flag = enable_debug = V; };

global.lithp_debug_flag = enable_debug;
global.lithp_get_debug = exports.get_debug_flag;
global.lithp_debug = debug;

var lithp_id = 0;
var lithp_instances = {};

global.get_lithp_instances = function() { return lithp_instances; };
global.get_lithp_max_id = function() { return lithp_id; };

var atexit_list = [];
global.lithp_atexit = function(handler) { atexit_list.push(handler); }

function exitHandler(options, err) {
	var written = false;
	atexit_list.forEach(H => H(options, err));
	//if (err) console.log(err.stack);
	if (options.exit) {
		if(written)
			process.exit();
		process.stderr.once('drain', function() {
			process.exit();
		});
	}
}

//do something when app is closing
process.on('exit', exitHandler.bind(null,{cleanup:true}));

//catches ctrl+c event
process.on('SIGINT', exitHandler.bind(null, {exit:true}));

//catches uncaught exceptions
//process.on('uncaughtException', exitHandler.bind(null, {exit:true}));

function Lithp () {
	this.functions = {};
	this.depth = 0;
	this.functioncalls = 0;
	this.id = lithp_id++;
	this.stopped = false;
	this.last_chain = null;
	lithp_instances[this.id] = this;
	(require('./builtins')).setup(this);
}
exports.Lithp = Lithp;
global.Lithp = Lithp;

Lithp.prototype.debug = debug;
Lithp.prototype.get_debug_flag = exports.get_debug_flag;

// Stop this instance and remove it from instances table.
Lithp.prototype.stop = function() {
	this.debug("Instance " + this.id + " stopping");
	delete lithp_instances[this.id];
	this.stopped = true;
};

/**
 * Defines a native function (ie, one that runs in the parent language,
 * in this case JavaScript) builtin.
 * These can be called like any other Lithp function.
 */
Lithp.prototype.builtin = function(name, params, body) {
	//debug("builtin, name: " + name + ", params:", params);
	if(name.indexOf("/") == -1) {
		name = name + "/" + params.length;
	}
	if(this.functions[name])
		0;//this.debug('Error: attempt to overwrite ' + name);
	else
		this.functions[name] = new FunctionDefinitionNative(name, params, body);
};

/**
 * Call a builtin library function of the given name (including /arity) and
 * return the value.
 * The arguments must already be resolved when given to this function.
 */
Lithp.prototype.CallBuiltin = function(chain, name, args) {
	if(!this.functions[name]) {
		name = name + "/" + args.length;
	}

	if(!this.functions[name]) {
		//console.log(this.functions);
		throw new Error("Cannot call builtin: " + name + " builtin not present");
	}
	return this.invoke_functioncall(chain, this.functions[name], args);
};

/**
 * Define a symbol in the top level definitions table.
 * This works by calling a an existing builtin function.
 */
Lithp.prototype.Define = function(chain, name, args) {
	this.CallBuiltin(chain, 'define/2', [name, args]);
};

/**
 * Get a defined symbol value.
 */
Lithp.prototype.Defined = function(chain, name) {
	return this.CallBuiltin(chain, 'get-def', [name]);
};

/**
 * Setup some default definitions for giving runtime code information about
 * the current environment.
 * It also brings in the currently defined builtin functions.
 */
Lithp.prototype.setupDefinitions = function(chain, file) {
	var filename = file;
	var dirname = "";
	if(file != "[evaluated code]") {
		filename = path.resolve(filename);
		dirname  = path.resolve(path.dirname(filename));
	}
	this.Define(chain, "__filename", filename);
	this.Define(chain, "__dirname", dirname);
	// Used by builtin import/1
	var base = path.resolve(__dirname + "/..");
	this.Define(chain, "_module_search_path", [
		'', base,
		base + "/modules",
		'.', './modules'
	]);
	this.Define(chain, "_modules_imported", []);
	this.Define(chain, "DEBUG", enable_debug ? Atom('true') : Atom('false'));
	// Pull in global definitions
	for(var Name in global._lithp_global_definitions) {
		var Value = global._lithp_global_definitions[Name];
		this.Define(chain, Name, Value);
	}
	var count = chain.importClosure(this.functions);
	this.debug("Standard library loaded " + count + " symbols");
};

// Pull in interpreter
global.Lithp = Lithp;
require('./interpreter');

}).call(this,require('_process'),typeof global !== "undefined" ? global : typeof self !== "undefined" ? self : typeof window !== "undefined" ? window : {},"/node_modules/lithp/lib")
},{"../package.json":56,"./builtins":11,"./interpreter":12,"./types":14,"./util":15,"_process":134,"path":133,"util":137}],14:[function(require,module,exports){
(function (global){
/**
 * Provide the basic Lithp structure types used by the interpreter.
 */

"use strict";
var util = require('util'),
    inspect = util.inspect;

function AtomValue (value, name) {
	this.value = value;
	this.type = 'Atom';
	this.name = name;
}
// This must not be changed, as it becomes the key for function names.
AtomValue.prototype.toString = function() {
	return this.name;
};

var atoms = {};
var atomid = 0;
function Atom (name) {
	if(!atoms[name]) {
		var atom = new AtomValue(++atomid, name);
		atoms[name] = atom;
		atoms[atomid] = atom;
	}
	return atoms[name];
}

exports.Atom = Atom;

var atomMissing = Atom('missing');

exports.GetAtoms = () => atoms;
exports.GetAtomsCount = () => atomid;

function Tuple () {
	this.value = Array.prototype.slice.call(arguments);
	this.length = this.value.length;
	this.type = 'Tuple';
	// Make all tuple items available via [index]
	for(var i = 0; i < this.value.length; i++)
		this[i] = this.value[i];
}
Tuple.prototype.get = function(n) { return this.value[n]; };
Tuple.prototype.length = function() { return this.value.length; };
Tuple.prototype.toString = function() {
	var parts = this.value.map(P => {
		if(!P)
			return inspect(P);
		if(typeof P == typeof "")
			return JSON.stringify(P);
		if(P.type == 'Atom')
			return "'" + P.name + "'";
		return P.toString()
	});
	return '{' + parts.join(', ') + '}';
};
exports.Tuple = Tuple;

var opchainclosure_id = 0;
exports.GetOpChainsCount = () => opchainclosure_id;
function OpChainClosure (owner, parent) {
	this.owner = owner;
	this.id = opchainclosure_id++;
	this.parent = parent;
	if(this.parent && this.parent.constructor == OpChain)
		this.parent = parent.closure;
	if(this.parent)
		if(this.parent.topmost)
			this.topmost = this.parent.topmost;
		else
			this.topmost = this.parent.getTopOwner();
	else
		this.topmost = this;
	this.closure = {};
}
OpChainClosure.prototype.getOwner = function() { return this.owner; };
OpChainClosure.prototype.getTopOwner = function() {
	if(this.parent)
		return this.parent.getTopOwner();
	return this;
};
OpChainClosure.prototype.defined = function(name) {
	//return Object.keys(this.closure).indexOf(name) != -1;
	return name in this.closure;
};
OpChainClosure.prototype.any_defined = function(name) {
	if(this.defined(name))
		return true;
	if(this.parent)
		return this.parent.any_defined(name);
	return false;
};
OpChainClosure.prototype._do_set = function(name, value) {
	if(value && value.constructor == LiteralValue)
		value = LiteralValue.value;
	//console.log("(Setting locally: " + name + " =", value, ")");
	this.closure[name] = value;
	return value;
};

OpChainClosure.prototype.set = function(name, value) {
	if(this.defined(name)) {
		return this._do_set(name, value);
	}
	if(this.parent) {
	//console.log("(OpChainClosure.set(" + name + ", " + value + ")");
	//console.log("(Parent is:", this.parent, ")");
		if(this.parent.try_set(name, value)) {
			//console.log("(result from parent.try_set: true)");
			return true;
		}
	}
	return this._do_set(name, value);
};
OpChainClosure.prototype.set_immediate = function(name, value) {
	return this._do_set(name, value);
};
OpChainClosure.prototype.try_set = function(name, value) {
	if(this.defined(name)) {
		this._do_set(name, value);
		return true;
	}
	if(this.parent) {
		return this.parent.try_set(name, value);
	} else if(global._lithp.set_toplevel === true) {
		this._do_set(name, value);
		return true;
	}
	return false;
};
OpChainClosure.prototype.get = function(name) {
	if(this.defined(name))
		return ["ok", this.closure[name]];
	if(this.parent)
		return this.parent.get(name);
	return [];
};
OpChainClosure.prototype.get_or_missing = function(name) {
	if(this.defined(name))
		return this.closure[name];
	if(this.parent)
		return this.parent.get_or_missing(name);
	return atomMissing;
};
OpChainClosure.prototype.getDefined = function(depth) {
	if(depth === undefined)
		depth = 1;
	
	var result = {};
	for(var k in this.closure)
		result[k] = this.closure[k];
	if(--depth > 0 && this.parent) {
		var parentDefines = this.parent.getDefined(depth);
		for(var k in parentDefines)
			result[k] = parentDefines[k];
	}

	return result;
};

var opchain_id = 0;
function OpChain (parent, ops) {
	this.parent = parent;
	this.id = opchain_id++;
	if(ops && ops.constructor !== Array)
		ops = [ops];
	this.ops = ops || [];
	this.closure = new OpChainClosure(this, parent);
	this.immediate = false;
	this.pos = -1;
}
OpChain.prototype.getTopParent = function() {
	if(this.parent)
		return this.parent.getTopParent();
	return this;
};
OpChain.prototype.importClosure = function(lib) {
	var count = 0;
	for(var k in lib) {
		//lithp_debug(" importClosure: import function " + k);
		this.closure.set_immediate(k, lib[k]);
		count++;
	}
	return count;
};
OpChain.prototype.push = function(e) {
	this.ops.push(e);
};
OpChain.prototype.rewind = function() {
	this.pos = -1;
};
OpChain.prototype.next = function() {
	//this.current = this.ops.shift();
	this.pos++;
	if(this.pos > this.ops.length)
		return undefined;
	return this.current = this.ops[this.pos];
};
OpChain.prototype.get = function() {
	return this.current;
};
OpChain.prototype.toString = function() {
	var ops = [];
	this.ops.forEach(Op => {
		ops.push(Op.toString());
	});
	return "OpChain [" + ops.join(',') + "]";
};
OpChain.prototype.call = function(variables) {
	var non_imm = new OpChain();
	non_imm.parent = this.parent;
	non_imm.ops = this.ops;
	non_imm.closure = new OpChainClosure(this, this);
	non_imm._set_variables(variables);
	non_imm.non_immediate = false;
	return non_imm;
};
OpChain.prototype.call_immediate = function(variables) {
	var imm = new OpChain();
	imm.parent = this.parent;
	imm.ops = this.ops;
	imm.closure = new OpChainClosure(this, this);
	imm._set_variables(variables);
	imm.immediate = true;
	return imm;
};
OpChain.prototype.replaceWith = function(repl) {
	this.ops = repl.fn_body.ops || [];
	this.rewind();
};

OpChain.prototype._set_variables = function(variables) {
	variables = variables || {};
	for(var name in variables)
		this.closure.set_immediate(name, variables[name]);
};

exports.OpChain = OpChain;

function LiteralValue (value) {
	this.value = value;
	this.type = typeof value;
}
LiteralValue.prototype.toString = function() {
	if(!this.value)
		return inspect(this.value);
	return this.value.toString();
};
exports.LiteralValue = LiteralValue;

function VariableReference (name) {
	this.ref = name;
}
VariableReference.prototype.toString = function() {
	return this.ref;
};
exports.VariableReference = VariableReference;

function FunctionCall (name, params, reentry) {
	// TODO: Later this will allow function reentry, but
	//       for now it just acts as a normal function call.
	//       This does mean head recursive functions can run
	//       out of stack space, but provides a much easier
	//       implementation.
	//this.fn__reentry = false;
	this.fn_args = params.length;
	this.fn_name = name;
	this.fn_params = params;
}
FunctionCall.prototype.toString = function() {
	return "FnCall " + this.fn_name;
};
exports.FunctionCall = FunctionCall;

function FunctionReentry (name, params) {
	return new FunctionCall(name, params, true);
}
exports.FunctionReentry = FunctionReentry;

function FunctionDefinition (parent, name, params, body) {
	// Keeps track of how many times this FunctionDefinition has been cloned.
	// It would most likely be cloned when used in scope/1.
	this.instance_id = 0;
	if(arguments.length > 0) {
		this.fn_name = name;
		this.fn_params = params;
		this.fn_body = new OpChain(parent, body);
		var m = name.match(/^([^A-Z][^\/]*)\/([0-9]+|\*)$/);
		if(!m)
			throw new Error("Could not parse function name for arity: " + inspect(name));
		this.arity = m[2] == '*' ? '*' : parseInt(m[2]);
		this.readable_name = m[1];
	}
	this.function_entry = this.readable_name;
}
FunctionDefinition.prototype.clone = function() {
	var obj = new FunctionDefinition();
	obj.fn_name = this.fn_name;
	obj.fn_params = this.fn_params;
	obj.fn_body = this.fn_body.call();
	obj.arity = this.arity;
	obj.readable_name = this.readable_name;
	obj.instance_id++;
	return obj;
};
FunctionDefinition.prototype.toString = function() {
	return "[FnDef:" + this.fn_name + ":" + this.instance_id + ", " + (this.scoped ? "scoped, " : "") +
		"params: " + this.fn_params.join(', ') +
		", body: " + this.fn_body.ops + "]";
};
exports.FunctionDefinition = FunctionDefinition;

var anonymous_counter = 0;
function AnonymousFunction (parent, params, body) {
	// Anonymous functions cannot have arity *
	var fn_name = "__anonymous" + (++anonymous_counter) + "/" + params.length;
	return new FunctionDefinition(parent, fn_name, params, body);
}
exports.AnonymousFunction = AnonymousFunction;

function FunctionDefinitionNative (name, params, body) {
	this.fn_name = name;
	this.fn_params = params;
	this.fn_body = body;
	var m = name.match(/^([^A-Z][^\/]*)\/([0-9]+|\*)$/);
	if(!m)
		throw new Error("Could not parse function name for arity: " + inspect(name));
	this.arity = m[2] == '*' ? '*' : parseInt(m[2]);
	this.readable_name = m[1];
}
exports.FunctionDefinitionNative = FunctionDefinitionNative;

}).call(this,typeof global !== "undefined" ? global : typeof self !== "undefined" ? self : typeof window !== "undefined" ? window : {})
},{"util":137}],15:[function(require,module,exports){
(function (global){
/**
 * Provides some additional utility functions.
 */

global.__lithp = {};
global.__lithp_define = function(Name, Value) { return global.__lithp[Name] = Value || 1; };
global.__lithp_defined = function(Name) { return Name in global.__lithp; };

if(!__lithp_defined('util')) {

__lithp_define('util');

// Add non-destructive methods of moving through an Array
Array.prototype.iterator = function() { return new ArrayIterator(this); };

function ArrayIterator (arr) {
	this.array = arr;
	if(arr.length > 0)
		this.refresh(arr);
	else
		this.index = -1;
	this.rewind();
}

ArrayIterator.prototype.rewind = function() { this.index = 0; };
ArrayIterator.prototype.next   = function() {
	if(this.index >= this.array.length)
		return undefined;
	return this.get(this.index++);
};
ArrayIterator.prototype.prev = function() {
	if(this.index == -1)
		throw new Error("Cannot move before first element");
	this.index--;
	return this.get(this.index);
};
ArrayIterator.prototype.get = function(index) {
	if(index === undefined)
		index = this.index;
	return this.array[index];
};
ArrayIterator.prototype.set = function(index, val) {
	if(index === undefined)
		index = this.index;
	this.array[index] = val;
	this.refresh();
};
ArrayIterator.prototype.set_current = function(val) {
	this.set(this.index, val);
};

ArrayIterator.prototype.push = function(val) {
	//console.log("Pushing: ", val);
	this.array.push(val);
	this.refresh(this.array);
	return this.next();
};

ArrayIterator.prototype.pop = function() {
	var val = this.array.pop();
	this.refresh(this.array);
	if(this.index > this.length)
		this.index = this.length;
	return this.get();
};

ArrayIterator.prototype.refresh = function(arr) {
	this.length = this.array.length;
};

Object.clone = function(src) { return Object.assign({}, src); };

/*
	Taken from: http://stackoverflow.com/questions/10539938/override-the-equivalence-comparison-in-javascript

	Object.equals

	Desc:       Compares an object's properties with another's, return true if the objects
	            are identical.
	params:
		obj = Object for comparison
*/
Object.equals = function(a, b)
{
	/*Make sure the object is of the same type as this*/
	if(typeof b != typeof a)
		return false;

	/*Iterate through the properties of a bect looking for a discrepancy between a and b*/
	for(var property in a)
	{

		/*Return false if b doesn't have the property or if its value doesn't match a' value*/
		if(typeof b[property] == "undefined")
			return false;   
		if(b[property] != a[property])
			return false;
	}

	/*Object's properties are equivalent */
	return true;
}

/*
	Taken from: http://stackoverflow.com/questions/5072136/javascript-filter-for-objects

	Object.filter

	Desc:       Filters an object using a function. Modified for better usage.

	params:
		obj       = Object to filter
		predicate = function(Key, Value) => bool (true to keep, false to discard)
*/
Object.filter = function(obj, predicate) {
	var result = {}, key;
	for(key in obj)
		if(obj.hasOwnProperty(key) && predicate(key, obj[key]))
			result[key] = obj[key];
	return result;
};

global.timeCall = function(Title, Callback) {
	var start = new Date().getTime();
	var value = Callback();
	var total = new Date().getTime() - start;
	return [value, total];
};

} // if(!__lithp_defined('util'))

}).call(this,typeof global !== "undefined" ? global : typeof self !== "undefined" ? self : typeof window !== "undefined" ? window : {})
},{}],16:[function(require,module,exports){
module.exports = "#!/usr/bin/env lithp-macro\n% Test the preprocessor. See -m flag above.\n(\n\t(import lists)\n\t(import match)\n\t(def fac #N :: (\n\t\t% { starts a (scope #) section.\n\t\t% } closes it.\n\t\t(when (tuple {== 0 N} {1})\n\t\t      (tuple {true}   {* N (fac (- N 1))})\n\t\t)\n\t))\n\t(print (fac 10))\n\t% [ starts a list.\n\t% ] closes it.\n\t(print [1 2 3 4])\n\n\t(def count-items-inner #Ele :: (\n\t\t(when\n\t\t\t(tuple {is-list Ele} {count-items Ele})\n\t\t\t(tuple {true}        {1})\n\t\t)\n\t))\n\t(def count-items #List :: ((foldl List 0 #I,A :: ((+ A (count-items-inner I))))))\n\t(print (count-items [1 2 [3 4 [5 6] 7] 8]))\n)\n\n";

},{}],17:[function(require,module,exports){
module.exports = "#!/usr/bin/env lithp\n% Lithp macro preprocessor\n(\n\t(import class)\n\t(import file)\n\t(import lists)\n\t(import stream)\n\n\t(def get-basedir #Dir :: (\n\t\t(var Possibilities (list \"\" \"node_modules/lithp/\" \"../\" \"../node_modules/lithp/\"))\n\t\t(get-basedir (head Possibilities) (tail Possibilities) Dir)\n\t))\n\n\t(def get-basedir #Head,Tail,Dir :: (\n\t\t(var Actual (+ Head Dir))\n\t\t(try (\n\t\t\t(read-dir Actual)\n\t\t\t(Actual)\n\t\t) (catch # :: (\n\t\t\t(if (> (length Tail) 0) (\n\t\t\t\t(next get-basedir (head Tail) (tail Tail) Dir)\n\t\t\t) (else (\n\t\t\t\t(throw \"Cannot find macro\")\n\t\t\t)))\n\t\t)))\n\t))\n\n\t% Macro Preprocessor Class\n\t(var MacroPreprocessor (class 'MacroPreprocessorClass'\n\t\t(tuple (class-init) #Self,BaseDir :: (\n\t\t\t(var Dir (get-basedir BaseDir))\n\n\t\t\t(var Files (filter (read-dir Dir) #N :: (\n\t\t\t\t(!= (null) (match N (regex \"\\\\.h$\")))\n\t\t\t)))\n\n\t\t\t(var Definitions (list))\n\t\t\t(each Files (scope #File :: (\n\t\t\t\t(set Definitions (++ Definitions (list (new Definition File))))\n\t\t\t)))\n\n\t\t\t(member-set Self definitions Definitions)\n\t\t))\n\t\t(tuple parse #Self,File :: (\n\t\t\t(foldl (member-get Self definitions) File #Def,Acc :: (\n\t\t\t\t(member-call Def parse Acc)\n\t\t\t))\n\t\t))\n\t))\n\n\t% Definitions class.\n\t(var Definition (class 'DefinitionClass'\n\t\t(tuple (class-init) #Self,File :: (\n\t\t\t(var Contents (read-lines (+ Dir \"/\" File)))\n\t\t\t(var Definitions (dict))\n\t\t\t(dict-set Definitions '__FILE__' (resolve File))\n\t\t\t(member-set Self definitions (member-call Self parse-contents Contents Definitions))\n\t\t\t%(print (member-get Self definitions))\n\t\t))\n\t\t(tuple parse-contents #Self,Contents,Definitions :: (\n\t\t\t(if (== 0 (length Contents)) (\n\t\t\t\t(Definitions)\n\t\t\t) (else (\n\t\t\t\t(while ((> (length Contents) 0)) (\n\t\t\t\t\t(var Line (head Contents))\n\t\t\t\t\t(set Contents (tail Contents))\n\t\t\t\t\t(var Match (match Line (regex\n\t\t\t\t\t\t\"^\\\\s*#([a-z]+)(?:\\\\s+([^ ]+))?(?:\\\\s+(.+))?\\\\s*$\")\n\t\t\t\t\t))\n\t\t\t\t\t(if (!= (null) Match) (\n\t\t\t\t\t\t(var Directive (index Match 1))\n\t\t\t\t\t\t(var Name      (index Match 2))\n\t\t\t\t\t\t(var Value     (index Match 3))\n\t\t\t\t\t\t(if (== \"define\" Directive) (\n\t\t\t\t\t\t\t(dict-set Definitions Name Value)\n\t\t\t\t\t\t\t%(print \"Defining \" Name \" => \" Value)\n\t\t\t\t\t\t) (else (\n\t\t\t\t\t\t\t(throw (+ \"Unknown directive: \" Directive))\n\t\t\t\t\t\t)))\n\t\t\t\t\t))\n\t\t\t\t))\n\t\t\t\t(Definitions)\n\t\t\t)))\n\t\t))\n\t\t(tuple add-def #Self,Search,Replace :: (\n\t\t\t(var Definitions (member-get Self definitions))\n\t\t\t(if (dict-present Definitions Search) (\n\t\t\t\t(throw (+ \"Attempted redefinition of \" Search))\n\t\t\t))\n\t\t\t(dict-set Definitions Search Replace)\n\t\t\t(Self)\n\t\t))\n\t\t(tuple get-defs #Self :: (\n\t\t\t(member-get Self definitions)\n\t\t))\n\t\t(tuple parse #Self,Contents :: (\n\t\t\t(var Definitions (member-get Self definitions))\n\t\t\t(foldl (dict-keys Definitions) Contents (scope #Def,Result :: (\n\t\t\t\t(var Search (get Def))\n\t\t\t\t(var Replace (dict-get Definitions Def))\n\t\t\t\t(replace Result (regex Search g) Replace)\n\t\t\t)))\n\t\t))\n\t))\n\n\t% Classes defined. Instantiate preprocessor\n\t(var Preprocessor (new MacroPreprocessor \"macro\"))\n\n\t%(var TestCode \"(def f #N :: ((when (tuple {== 0 N} {1}) (tuple {atom true} {fac (- N 1)))))\")\n\t(if (get-def '__MAIN__') (\n\t\t(var TestCode (readInputStream))\n\t\t(print (member-call Preprocessor parse TestCode))\n\t))\n\n\t(def macro-preprocessor #Contents :: (\n\t\t(member-call Preprocessor parse Contents)\n\t))\n\t(export-global macro-preprocessor/1)\n)\n";

},{}],18:[function(require,module,exports){
module.exports=[[["def","assert",{"code":[[["if",["!","Result"],[["throw",["+","\"Assert failed:\"","Description"]]]],["atom","true"]]],"_fndef":true,"_fnparams":["Result","Description"]}],["def","assert",{"code":[[["if",["!","Result"],[["throw","\"Assert failed\""]]],["atom","true"]]],"_fndef":true,"_fnparams":["Result"]}],["export-global","assert/1","assert/2"],["def","exception-message",{"code":[[["index","E","message"]]],"_fndef":true,"_fnparams":["E"]}],["export-global","exception-message/1"],["if",["get-def","'ASSERT_TEST'"],[["try",[["assert",["==","0","1"],"\"Mismatch check\""]],["catch",{"code":[[["print","\"Mismatch check success\""]]],"_fndef":true,"_fnparams":[]}]],["try",[["assert",["!=","0","0"],"\"Equality check\""],["throw","\"Equality check issue\""]],["catch",{"code":[[["if",["==",["exception-message","E"],"\"Equality check issue\""],[["throw","E"]],["else",[["print","\"Equality check success\""]]]]]],"_fndef":true,"_fnparams":["E"]}]]]]]]
},{}],19:[function(require,module,exports){
module.exports = "%% assert.lithp\n%% Provides assertion functions.\n(\n\t(def assert #Result,Description :: (\n\t\t(if (! Result) (\n\t\t\t(throw (+ \"Assert failed:\" Description))\n\t\t))\n\t\t% TODO: Fix parser bug\n\t\t(atom true)\n\t))\n\t(def assert #Result :: (\n\t\t(if (! Result) (\n\t\t\t(throw \"Assert failed\")\n\t\t))\n\t\t% TODO: Fix parser bug\n\t\t(atom true)\n\t))\n\n\t(export-global assert/1 assert/2)\n\n\t(def exception-message #E :: ((index E message)))\n\n\t(export-global exception-message/1)\n\n\t(if (get-def 'ASSERT_TEST') (\n\t\t(try (\n\t\t\t(assert (== 0 1) \"Mismatch check\")\n\t\t) (catch # :: (\n\t\t\t(print \"Mismatch check success\")\n\t\t)))\n\n\t\t(try (\n\t\t\t(assert (!= 0 0) \"Equality check\")\n\t\t\t(throw \"Equality check issue\")\n\t\t) (catch #E :: (\n\t\t\t(if (== (exception-message E) \"Equality check issue\") (\n\t\t\t\t(throw E)\n\t\t\t) (else (\n\t\t\t\t(print \"Equality check success\")\n\t\t\t)))\n\t\t)))\n\t))\n)\n";

},{}],20:[function(require,module,exports){
module.exports=[[["try",[["var","Bignum",["require","\"bignum\""]],["def","bignum",{"code":[[["call","Bignum","Value"]]],"_fndef":true,"_fnparams":["Value"]}],["def","b+",{"code":[[["invoke","A","add","B"]]],"_fndef":true,"_fnparams":["A","B"]}],["def","b-",{"code":[[["invoke","A","sub","B"]]],"_fndef":true,"_fnparams":["A","B"]}],["def","b*",{"code":[[["invoke","A","mul","B"]]],"_fndef":true,"_fnparams":["A","B"]}],["def","b//2",{"code":[[["invoke","A","div","B"]]],"_fndef":true,"_fnparams":["A","B"]}],["def","babs",{"code":[[["invoke","N","abs"]]],"_fndef":true,"_fnparams":["N"]}],["def","bneg",{"code":[[["invoke","N","neg"]]],"_fndef":true,"_fnparams":["N"]}],["def","b>",{"code":[[["==",["invoke","A","gt","B"],["true"]]]],"_fndef":true,"_fnparams":["A","B"]}],["def","b>=",{"code":[[["==",["invoke","A","ge","B"],["true"]]]],"_fndef":true,"_fnparams":["A","B"]}],["def","b<",{"code":[[["==",["invoke","A","lt","B"],["true"]]]],"_fndef":true,"_fnparams":["A","B"]}],["def","b<=",{"code":[[["==",["invoke","A","le","B"],["true"]]]],"_fndef":true,"_fnparams":["A","B"]}],["def","b==",{"code":[[["==",["invoke","A","eq","B"],["true"]]]],"_fndef":true,"_fnparams":["A","B"]}],["def","bpow",{"code":[[["invoke","A","pow","B"]]],"_fndef":true,"_fnparams":["A","B"]}],["def","bpowm",{"code":[[["invoke","A","powm","N","M"]]],"_fndef":true,"_fnparams":["A","N","M"]}],["def","binvertm",{"code":[[["invoke","A","invertm","M"]]],"_fndef":true,"_fnparams":["N","M"]}],["def","brand",{"code":[[["call","Bignum","rand"]]],"_fndef":true,"_fnparams":[]}],["def","brand",{"code":[[["call","Bignum","rand","U"]]],"_fndef":true,"_fnparams":["U"]}],["def","bsqrt",{"code":[[["invoke","N","sqrt"]]],"_fndef":true,"_fnparams":["N"]}],["def","broot",{"code":[[["invoke","N","root","M"]]],"_fndef":true,"_fnparams":["N","M"]}],["def","b<<",{"code":[[["invoke","N","shiftLeft","S"]]],"_fndef":true,"_fnparams":["N","S"]}],["def","b>>",{"code":[[["invoke","N","shiftRight","S"]]],"_fndef":true,"_fnparams":["N","S"]}],["def","bgcd",{"code":[[["invoke","N","gcd","M"]]],"_fndef":true,"_fnparams":["N","M"]}],["def","bjacobi",{"code":[[["invoke","N","jacobi","M"]]],"_fndef":true,"_fnparams":["N","M"]}],["export-global","bignum/1"],["export-global","b+/2","b-/2","b*/2","b//2"],["export-global","babs/1","bneg/1"],["export-global","b>/2","b>=/2","b</2","b<=/2","b==/2"],["export-global","bpow/2","bpowm/3","binvertm/2"],["export-global","brand/0","brand/1","bsqrt/1","broot/2"],["export-global","b<</2","b>>/2","bgcd/2","bjacobi/2"],["import","\"lists\""],["def","bsum",{"code":[[["foldl","L",["bignum","0"],["scope",{"code":[[["b+","N","A"]]],"_fndef":true,"_fnparams":["N","A"]}]]]],"_fndef":true,"_fnparams":["L"]}],["def","bprod",{"code":[[["foldl","L",["bignum","1"],["scope",{"code":[[["b*","A",["bignum","N"]]]],"_fndef":true,"_fnparams":["N","A"]}]]]],"_fndef":true,"_fnparams":["L"]}],["export-global","bsum/1","bprod/1"],["if",["get-def","'TEST'"],[["var","N1",["bignum","\"782910138827292261791972728324982\""]],["var","N2",["bignum","\"612948285478570042376183478471174272694879005539119746287405300324\""]],["print",["to-string",["b+","N1","N2"]]],["print",["to-string",["b-","N1","N2"]]],["print",["to-string",["b*","N1","N2"]]],["print",["to-string",["b/","N2","N1"]]],["print",["b>","N1","N2"]],["print",["b>=","N2","N1"]],["print",["brand"]],["print",["brand","2"]],["print",["bsum",["list","N1","N2"]]]]]],["catch",{"code":[[["print","\"bignum module not available\""]]],"_fndef":true,"_fnparams":["E"]}]]]]
},{}],21:[function(require,module,exports){
module.exports = "% Uses the NodeJS Bignum module and provides arithmatic functions.\n%\n% All arithmatic functions are prefixed with 'b'.\n(\n\t(try (\n\t\t(var Bignum (require \"bignum\"))\n\t\t(def bignum #Value :: ((call Bignum Value)))\n\n\t\t(def b+ #A,B :: ((invoke A add B)))\n\t\t(def b- #A,B :: ((invoke A sub B)))\n\t\t(def b* #A,B :: ((invoke A mul B)))\n\t\t(def b//2 #A,B :: ((invoke A div B)))\n\t\t(def babs #N :: ((invoke N abs)))\n\t\t(def bneg #N :: ((invoke N neg)))\n\t\t(def b> #A,B :: ((== (invoke A gt B) (true))))\n\t\t(def b>= #A,B :: ((== (invoke A ge B) (true))))\n\t\t(def b< #A,B :: ((== (invoke A lt B) (true))))\n\t\t(def b<= #A,B :: ((== (invoke A le B) (true))))\n\t\t(def b== #A,B :: ((== (invoke A eq B) (true))))\n\t\t(def bpow #A,B :: ((invoke A pow B)))\n\t\t(def bpowm #A,N,M :: ((invoke A powm N M)))\n\t\t(def binvertm #N,M :: ((invoke A invertm M)))\n\t\t(def brand # :: ((call Bignum rand)))\n\t\t(def brand #U :: ((call Bignum rand U)))\n\t\t(def bsqrt #N :: ((invoke N sqrt)))\n\t\t(def broot #N,M :: ((invoke N root M)))\n\t\t(def b<< #N,S :: ((invoke N shiftLeft S)))\n\t\t(def b>> #N,S :: ((invoke N shiftRight S)))\n\t\t(def bgcd #N,M :: ((invoke N gcd M)))\n\t\t(def bjacobi #N,M :: ((invoke N jacobi M)))\n\n\t\t(export-global bignum/1)\n\t\t(export-global b+/2 b-/2 b*/2 b//2)\n\t\t(export-global babs/1 bneg/1)\n\t\t(export-global b>/2 b>=/2 b</2 b<=/2 b==/2)\n\t\t(export-global bpow/2 bpowm/3 binvertm/2)\n\t\t(export-global brand/0 brand/1 bsqrt/1 broot/2)\n\t\t(export-global b<</2 b>>/2 bgcd/2 bjacobi/2)\n\n\t\t(import \"lists\")\n\t\t(def bsum #L :: ((foldl L (bignum 0) (scope #N,A :: ((b+ N A))))))\n\t\t(def bprod #L :: ((foldl L (bignum 1) (scope #N,A :: ((b* A (bignum N)))))))\n\n\t\t(export-global bsum/1 bprod/1)\n\n\t\t(if (get-def 'TEST') (\n\t\t\t(var N1 (bignum \"782910138827292261791972728324982\"))\n\t\t\t(var N2 (bignum \"612948285478570042376183478471174272694879005539119746287405300324\"))\n\t\t\t(print (to-string (b+ N1 N2)))\n\t\t\t(print (to-string (b- N1 N2)))\n\t\t\t(print (to-string (b* N1 N2)))\n\t\t\t(print (to-string (b/ N2 N1)))\n\t\t\t(print (b> N1 N2))\n\t\t\t(print (b>= N2 N1))\n\t\t\t(print (brand))\n\t\t\t(print (brand 2))\n\t\t\t(print (bsum (list N1 N2)))\n\t\t))\n\t) (catch #E :: (\n\t\t(print \"bignum module not available\")\n\t)))\n)\n";

},{}],22:[function(require,module,exports){
module.exports=[[["try",[["var","Buffer",["index",["require","\"buffer\""],"\"Buffer\""]],["var","DefaultBufferSize","1024"],["def","buffer",{"code":[[["buffer","DefaultBufferSize"]]],"_fndef":true,"_fnparams":[]}],["def","buffer",{"code":[[["call","Buffer","Size"]]],"_fndef":true,"_fnparams":["Size"]}],["export-global","buffer/0","buffer/1"],["if",["get-def","'TEST'"],[["print","\"A buffer: \"",["buffer"]]]]],["catch",{"code":[[["print","\"Buffer module unavailable\""]]],"_fndef":true,"_fnparams":[]}]]]]
},{}],23:[function(require,module,exports){
module.exports = "% Module: buffer\n%\n% Provides functions for working with buffers.\n(\n\t(try (\n\t\t(var Buffer (index (require \"buffer\") \"Buffer\"))\n\n\t\t(var DefaultBufferSize 1024)\n\t\t(def buffer # :: ((buffer DefaultBufferSize)))\n\t\t(def buffer #Size :: (\n\t\t\t(call Buffer Size)\n\t\t))\n\n\t\t(export-global buffer/0 buffer/1)\n\n\t\t(if (get-def 'TEST') (\n\t\t\t(print \"A buffer: \" (buffer))\n\t\t))\n\t) (catch # :: (\n\t\t(print \"Buffer module unavailable\")\n\t)))\n)\n";

},{}],24:[function(require,module,exports){
module.exports=[[["var","Cache",["dict"]],["def","cache-result",["scope",{"code":[[["var","Dict",["dict-get","Cache","Name"]],["if",["==",["null"],"Dict"],[["dict-set","Cache","Name",["dict"]],["set","Dict",["dict-get","Cache","Name"]]]],["if",["dict-present","Dict","Value"],[["dict-get","Dict","Value"]],["else",[["var","R",["call","Function","Value"]],["dict-set","Dict","Value","R"],"R"]]]]],"_fndef":true,"_fnparams":["Value","Name","Function"]}]],["export-global","cache-result/3"],["if",["get-def","'TEST'"],[["def","myf",{"code":[[["if",["<","N","2"],["1"],[["+",["cache-result",["-","N","1"],"myf",["get","\"myf/1\""]],["cache-result",["-","N","2"],"myf",["get","\"myf/1\""]]]]]]],"_fndef":true,"_fnparams":["N"]}],["print","myf","15"],["import","\"lists\""],["each",["seq","1","15"],["scope",{"code":[[["print","\" \"","N","\":\"",["myf","N"]]]],"_fndef":true,"_fnparams":["N"]}]]]]]]
},{}],25:[function(require,module,exports){
module.exports = "(\n\t% Caches calls\n\t(var Cache (dict))\n\n\t(def cache-result (scope #Value,Name,Function :: (\n\t\t(var Dict (dict-get Cache Name))\n\t\t(if (== (null) Dict) (\n\t\t\t(dict-set Cache Name (dict))\n\t\t\t(set Dict (dict-get Cache Name))\n\t\t))\n\t\t(if (dict-present Dict Value) (\n\t\t\t(dict-get Dict Value)\n\t\t) (else (\n\t\t\t(var R (call Function Value))\n\t\t\t(dict-set Dict Value R)\n\t\t\tR\n\t\t)))\n\t)))\n\n\t(export-global cache-result/3)\n\n\t(if (get-def 'TEST') (\n\t\t(def myf #N :: (\n\t\t\t(if (< N 2) (1) (\n\t\t\t\t(+ (cache-result (- N 1) myf (get \"myf/1\"))\n\t\t\t\t   (cache-result (- N 2) myf (get \"myf/1\")))\n\t\t\t))\n\t\t))\n\t\t(print myf 15)\n\t\t(import \"lists\")\n\t\t(each (seq 1 15) (scope #N :: (\n\t\t\t(print \" \" N \":\" (myf N))\n\t\t)))\n\t))\n)\n";

},{}],26:[function(require,module,exports){
module.exports=[[["import","lists"],["def","class-init",{"code":[[["\"__init\""]]],"_fndef":true,"_fnparams":[]}],["def","class-class",{"code":[[["\"__class__\""]]],"_fndef":true,"_fnparams":[]}],["def","class-funcs",{"code":[[["\"__functions__\""]]],"_fndef":true,"_fnparams":[]}],["def","class-instc",{"code":[[["\"__instance__\""]]],"_fndef":true,"_fnparams":[]}],["export-global","class-init/0","class-class/0","class-funcs/0","class-instc/0"],["def","member-set",{"code":[[["dict-set","Instance","Name","Value"]]],"_fndef":true,"_fnparams":["Instance","Name","Value"]}],["def","member-get",{"code":[[["dict-get","Instance","Name"]]],"_fndef":true,"_fnparams":["Instance","Name"]}],["def","member-present",{"code":[[["dict-present","Instance","Name"]]],"_fndef":true,"_fnparams":["Instance","Name"]}],["export-global","member-set/3","member-get/2","member-present/2"],["def","member-call/*",{"code":[[["var","Self",["head","Args"]],["set","Args",["tail","Args"]],["var","Fun",["head","Args"]],["var","Params",["++",["list","Self"],["tail","Args"]]],["var","Instance",["member-get","Self",["class-instc"]]],["var","Funcs",["member-get","Instance",["class-funcs"]]],["var","Dest",["member-get","Funcs","Fun"]],["apply","Dest","Params"]]],"_fndef":true,"_fnparams":["Args"]}],["export-global","member-call/*"],["def","class/*",{"code":[[["var","Name",["head","Args"]],["var","Members",["tail","Args"]],["var","Instance",["dict"]],["dict-set","Instance",["class-class"],"Name"],["dict-set","Instance",["class-funcs"],["dict"]],["foldl","Members","Instance",{"code":[[["member-set",["dict-get","Self",["class-funcs"]],["index","Member","0"],["index","Member","1"]],["Self"]]],"_fndef":true,"_fnparams":["Member","Self"]}]]],"_fndef":true,"_fnparams":["Args"]}],["def","new/*",{"code":[[["var","Class",["head","Args"]],["var","Params",["tail","Args"]],["var","Instance",["dict"]],["member-set",["get","Instance"],["class-instc"],["get","Class"]],["if",["member-present",["member-get","Class",["class-funcs"]],["class-init"]],[["apply","member-call",["++",["list","Instance",["class-init"]],"Params"]]]],["Instance"]]],"_fndef":true,"_fnparams":["Args"]}],["export-global","class/*","new/*"],["if",["get-def","'CLASS_TEST'"],[["var","TestClass",["class","'TestClass'",["tuple",["class-init"],{"code":[[["member-set","Self","base","Base"]]],"_fndef":true,"_fnparams":["Self","Base"]}],["tuple","'add'",{"code":[[["to-string",["+","A","B"],["member-get","Self","base"]]]],"_fndef":true,"_fnparams":["Self","A","B"]}]]],["var","Base10",["new","TestClass","10"]],["var","Base2",["new","TestClass","2"]],["print",["member-call","Base10","add","5","10"]],["print",["member-call","Base2","add","5","10"]]]]]]
},{}],27:[function(require,module,exports){
module.exports = "% Implements a basic class system.\n% At present, inheritance is not supported.\n(\n\t(import lists)\n\n\t(def class-init  # :: ((\"__init\")))\n\t(def class-class # :: ((\"__class__\")))\n\t(def class-funcs # :: ((\"__functions__\")))\n\t(def class-instc # :: ((\"__instance__\")))\n\t(export-global class-init/0 class-class/0 class-funcs/0 class-instc/0)\n\n\t(def member-set  #Instance,Name,Value :: ((dict-set Instance Name Value)))\n\t(def member-get  #Instance,Name       :: ((dict-get Instance Name)))\n\t(def member-present #Instance,Name    :: ((dict-present Instance Name)))\n\t(export-global member-set/3 member-get/2 member-present/2)\n\n\t(def member-call/* #Args :: (\n\t\t(var Self     (head Args))\n\t\t(set Args     (tail Args))\n\t\t(var Fun      (head Args))\n\t\t% Params includes Self as the first member\n\t\t(var Params   (++ (list Self) (tail Args)))\n\t\t(var Instance (member-get Self (class-instc)))\n\t\t(var Funcs    (member-get Instance (class-funcs)))\n\t\t(var Dest     (member-get Funcs Fun))\n\t\t(apply Dest Params)\n\t))\n\t(export-global member-call/*)\n\n\t(def class/* #Args :: (\n\t\t(var Name (head Args))\n\t\t(var Members (tail Args))\n\t\t(var Instance (dict))\n\t\t(dict-set Instance (class-class) Name)\n\t\t(dict-set Instance (class-funcs) (dict))\n\t\t(foldl Members Instance #Member,Self :: (\n\t\t\t(member-set (dict-get Self (class-funcs)) (index Member 0) (index Member 1))\n\t\t\t(Self)\n\t\t))\n\t))\n\t(def new/* #Args :: (\n\t\t(var Class (head Args))\n\t\t(var Params (tail Args))\n\t\t(var Instance (dict))\n\t\t(member-set (get Instance) (class-instc) (get Class))\n\t\t(if (member-present (member-get Class (class-funcs)) (class-init)) (\n\t\t\t(apply member-call (++ (list Instance (class-init)) Params))\n\t\t))\n\t\t(Instance)\n\t))\n\n\t(export-global class/* new/*)\n\n\t(if (get-def 'CLASS_TEST') (\n\t\t(var TestClass (class 'TestClass'\n\t\t\t(tuple (class-init) #Self,Base :: (\n\t\t\t\t(member-set Self base Base)\n\t\t\t))\n\t\t\t(tuple 'add' #Self,A,B :: (\n\t\t\t\t(to-string (+ A B) (member-get Self base))\n\t\t\t))\n\t\t))\n\n\t\t% Base 10 version\n\t\t(var Base10 (new TestClass 10))\n\t\t% Base 2 version\n\t\t(var Base2  (new TestClass 2))\n\n\t\t(print (member-call Base10 add 5 10))\n\t\t(print (member-call Base2  add 5 10))\n\t))\n)\n\n";

},{}],28:[function(require,module,exports){
module.exports=[[["import","\"lists\""],["try",[["var","FS",["require","\"fs\""]],["var","Path",["require","\"path\""]],["def","resolve",{"code":[[["invoke","Path","resolve","Filename"]]],"_fndef":true,"_fnparams":["Filename"]}],["export-global","resolve/1"],["def","read-file",{"code":[[["set","Filename",["invoke","Path","resolve","Filename"]],["invoke","FS","readFileSync","Filename"]]],"_fndef":true,"_fnparams":["Filename"]}],["def","read-file",{"code":[[["set","Filename",["invoke","Path","resolve","Filename"]],["invoke","FS","readFile","Filename",["js-bridge","Callback"]]]],"_fndef":true,"_fnparams":["Filename","Callback"]}],["def","file-exists",{"code":[[["==",["true"],["invoke","FS","existsSync","Path"]]]],"_fndef":true,"_fnparams":["Path"]}],["def","is-file",{"code":[[["==",["true"],["invoke",["file-lstat","Path"],"isFile"]]]],"_fndef":true,"_fnparams":["Path"]}],["def","is-directory",{"code":[[["and",["!",["is-file","Path"]],["file-exists","Path"]]]],"_fndef":true,"_fnparams":["Path"]}],["def","file-lstat",{"code":[[["try",[["invoke","FS","lstatSync","Path"]],["catch",{"code":[[["lstat-empty","Path"]]],"_fndef":true,"_fnparams":["E"]}]]]],"_fndef":true,"_fnparams":["Path"]}],["def","read-dir",{"code":[[["invoke","FS","readdirSync","Path"]]],"_fndef":true,"_fnparams":["Path"]}],["export-global","read-dir/1"],["var","LStatMembers",["list","\"dev\"","\"mode\"","\"nlink\"","\"uid\"","\"gid\"","\"rdev\"","\"blksize\"","\"ino\"","\"size\"","\"blocks\"","\"atime\"","\"mtime\"","\"ctime\"","\"birthtime\""]],["def","lstat-empty",{"code":[[["var","Result",["dict"]],["each","LStatMembers",["scope",{"code":[[["dict-set","Result","M","0"]]],"_fndef":true,"_fnparams":["M"]}]],["dict-set","Result","isFile",["js-bridge",{"code":[[["false"]]],"_fndef":true,"_fnparams":[]}]],["get","Result"]]],"_fndef":true,"_fnparams":["Path"]}],["export-global","read-file/1","read-file/2","file-exists/1","is-file/1","is-directory/1","file-lstat/1"],["def","read-lines",{"code":[[["split",["to-string",["read-file","File"]],["regex","\"\\\\r?\\\\n\""]]]],"_fndef":true,"_fnparams":["File"]}],["export-global","read-lines/1"],["if",["==","true",["get-def","'TEST'"]],[["read-file","\"index.js\"",{"code":[[["print","\"Got Err:\"","Err"],["if",["!=",["undefined"],"Data"],[["print","\"Got Data:\"",["to-string","Data"]]]]]],"_fndef":true,"_fnparams":["Err","Data"]}],["print",["file-exists","\"run\""]],["print",["is-file","\"run\""]],["print",["is-file","\"src\""]],["print",["is-directory","\"src\""]],["print",["file-lstat","\"run1\""]],["print",["is-file","\"run1\""]]]]],["catch",{"code":[[["print","\"file module unavailable\""]]],"_fndef":true,"_fnparams":[]}]]]]
},{}],29:[function(require,module,exports){
module.exports = "% Provides file IO functions\n(\n\t(import \"lists\")\n\n\t(try (\n\t\t(var FS (require \"fs\"))\n\t\t(var Path (require \"path\"))\n\n\t\t(def resolve #Filename :: ((invoke Path resolve Filename)))\n\t\t(export-global resolve/1)\n\n\t\t(def read-file #Filename :: (\n\t\t\t(set Filename (invoke Path resolve Filename))\n\t\t\t(invoke FS readFileSync Filename)\n\t\t))\n\n\t\t(def read-file #Filename,Callback :: (\n\t\t\t(set Filename (invoke Path resolve Filename))\n\t\t\t(invoke FS readFile Filename (js-bridge Callback))\n\t\t))\n\n\t\t(def file-exists #Path :: ((== (true) (invoke FS existsSync Path))))\n\t\t(def is-file #Path :: ((== (true) (invoke (file-lstat Path) isFile))))\n\t\t(def is-directory #Path :: ((and (! (is-file Path)) (file-exists Path))))\n\t\t(def file-lstat #Path :: (\n\t\t\t(try (\n\t\t\t\t(invoke FS lstatSync Path)\n\t\t\t) (catch #E :: (\n\t\t\t\t(lstat-empty Path)\n\t\t\t)))\n\t\t))\n\n\t\t(def read-dir #Path :: (\n\t\t\t(invoke FS readdirSync Path)\n\t\t))\n\n\t\t(export-global read-dir/1)\n\n\t\t(var LStatMembers (list \"dev\" \"mode\" \"nlink\" \"uid\" \"gid\" \"rdev\" \"blksize\" \"ino\"\n\t\t\t\t\t\t\t\t\"size\" \"blocks\" \"atime\" \"mtime\" \"ctime\" \"birthtime\"))\n\t\t(def lstat-empty #Path :: (\n\t\t\t(var Result (dict))\n\t\t\t% Set each member to 0\n\t\t\t(each LStatMembers (scope #M :: ((dict-set Result M 0))))\n\t\t\t% Fake the isFile function\n\t\t\t(dict-set Result isFile (js-bridge # :: ((false))))\n\t\t\t(get Result)\n\t\t))\n\n\t\t% Deprecated: (export-global readFileAsync/2)\n\t\t(export-global read-file/1 read-file/2 file-exists/1 is-file/1 is-directory/1 file-lstat/1)\n\n\t\t(def read-lines #File :: (\n\t\t\t(split (to-string (read-file File)) (regex \"\\\\r?\\\\n\"))\n\t\t))\n\n\t\t(export-global read-lines/1)\n\n\t\t(if (== true (get-def 'TEST')) (\n\t\t\t(read-file \"index.js\" #Err,Data :: (\n\t\t\t\t(print \"Got Err:\" Err)\n\t\t\t\t(if (!= (undefined) Data) (\n\t\t\t\t\t(print \"Got Data:\" (to-string Data))\n\t\t\t\t))\n\t\t\t))\n\n\t\t\t(print (file-exists \"run\"))\n\t\t\t(print (is-file \"run\"))\n\t\t\t(print (is-file \"src\"))\n\t\t\t(print (is-directory \"src\"))\n\t\t\t(print (file-lstat \"run1\"))\n\t\t\t(print (is-file \"run1\"))\n\t\t))\n\t) (catch # :: (\n\t\t(print \"file module unavailable\")\n\t)))\n)\n";

},{}],30:[function(require,module,exports){
module.exports=[[["if",["get-def","'NATIVE'"],[["print","\"Using NATIVE lists functions\""]]],["if",["get-def","'NATIVE'"],[["def","map",{"code":[[["map-inner",["list"],"List","Callback"]]],"_fndef":true,"_fnparams":["List","Callback"]}]]],["def","map-inner",{"code":[[["if",["==","0",["length","List"]],[["Acc"]],["else",[["recurse",["++","Acc",["list",["call","Callback",["head","List"]]]],["tail","List"],"Callback"]]]]]],"_fndef":true,"_fnparams":["Acc","List","Callback"]}],["def","foldl",{"code":[[["if",["==","0",["length","List"]],[["Current"]],["else",[["recurse",["tail","List"],["call","Callback",["head","List"],"Current"],"Callback"]]]]]],"_fndef":true,"_fnparams":["List","Current","Callback"]}],["def","each",{"code":[[["each-inner","0","List","Callback"]]],"_fndef":true,"_fnparams":["List","Callback"]}],["def","each-inner",{"code":[[["if",["==","0",["length","List"]],[["atom","nil"]],["else",[["call","Callback",["head","List"],"Idx"],["recurse",["+","Idx","1"],["tail","List"],"Callback"]]]]]],"_fndef":true,"_fnparams":["Idx","List","Callback"]}],["def","each-idx",{"code":[[["each","List","Callback"]]],"_fndef":true,"_fnparams":["List","Callback"]}],["export-global","each/2","each-idx/2"],["def","seq",{"code":[[["seq","N0","N1",["?",["<","N0","N1"],"1","-1"]]]],"_fndef":true,"_fnparams":["N0","N1"]}],["def","seq",{"code":[[["set","L",["list"]],["var","N",["get","N0"]],["while",[["if",[">=","Inc","1"],[["<=","N","N1"]],[[">=","N","N1"]]]],[["set","L",["++","L",["list","N"]]],["set","N",["+","N","Inc"]]]],"L"]],"_fndef":true,"_fnparams":["N0","N1","Inc"]}],["export-global","map/2","foldl/3","each/2","seq/2","seq/3"],["if",["get-def","'NATIVE'"],[["var","PermutationsPossibilities",["list","0","1","2","6","24","120","720","5040","40320","362880","3628800","39916800","479001600"]],["def","permutations",{"code":[[["var","Length",["length","List"]],["var","Result",["list-fill",["index","PermutationsPossibilities","Length"],"0"]],["var","C",["list-fill","Length","0"]],["var","I","1"],["var","J","1"],["index-set","Result","0",["slice","List"]],["while",[["<","I","Length"]],[["var","CI",["index","C","I"]],["if",["<","CI","I"],[["var","K",["?",["@","I","2"],["get","CI"],"0"]],["var","P",["index","List","I"]],["index-set","List","I",["index","List","K"]],["index-set","List","K","P"],["index-set","C","I",["+","1","CI"]],["set","I","1"],["index-set","Result","J",["slice","List"]],["set","J",["+","1",["get","J"]]]],["else",[["index-set","C","I","0"],["set","I",["+","1",["get","I"]]]]]]]],["get","Result"]]],"_fndef":true,"_fnparams":["List"]}],["export-global","permutations/1"]]],["def","sum",{"code":[[["foldl","L","0",{"code":[[["+","N","A"]]],"_fndef":true,"_fnparams":["N","A"]}]]],"_fndef":true,"_fnparams":["L"]}],["def","prod",{"code":[[["foldl","L","1",{"code":[[["*","A","N"]]],"_fndef":true,"_fnparams":["N","A"]}]]],"_fndef":true,"_fnparams":["L"]}],["export-global","sum/1","prod/1"],["def","filter",{"code":[[["filter-inner","List","Predicate",["list"]]]],"_fndef":true,"_fnparams":["List","Predicate"]}],["def","filter-inner",{"code":[[["if",["==","0",["length","List"]],[["Acc"]],["else",[["var","Ele",["head","List"]],["if",["call","Predicate","Ele"],[["recurse",["tail","List"],"Predicate",["++","Acc",["list","Ele"]]]],["else",[["recurse",["tail","List"],"Predicate","Acc"]]]]]]]]],"_fndef":true,"_fnparams":["List","Predicate","Acc"]}],["export-global","filter/2"],["def","max/*",{"code":[[["set","List",["flatten","List"]],["foldl",["tail","List"],["head","List"],{"code":[[["?",[">","V","A"],"V","A"]]],"_fndef":true,"_fnparams":["V","A"]}]]],"_fndef":true,"_fnparams":["List"]}],["def","min/*",{"code":[[["set","List",["flatten","List"]],["foldl",["tail","List"],["head","List"],{"code":[[["?",["<","V","A"],"V","A"]]],"_fndef":true,"_fnparams":["V","A"]}]]],"_fndef":true,"_fnparams":["List"]}],["export-global","min/*","max/*"],["if",["get-def","'NATIVE'"],[["def","flat-map",{"code":[[["apply","++",["++",["list"],["map","List","Callback"]]]]],"_fndef":true,"_fnparams":["List","Callback"]}]]],["def","lcomp",{"code":[[["lcomp-inner",["list"],["head","Generators"],"Handler",["tail","Generators"],"Filter"]]],"_fndef":true,"_fnparams":["Handler","Generators","Filter"]}],["def","lcomp",{"code":[[["lcomp","Handler","Generators",{"code":[[["atom","true"]]],"_fndef":true,"_fnparams":[]}]]],"_fndef":true,"_fnparams":["Handler","Generators"]}],["def","lcomp-inner",{"code":[[["flat-map","List",["scope",{"code":[[["var","Current",["++","Base",["list","Ele"]]],["if",[">",["length","Generators"],"0"],[["lcomp-inner","Current",["head","Generators"],"Handler",["tail","Generators"],"Filter"]],["else",[["if",["apply","Filter","Current"],[["list",["apply","Handler","Current"]]],["else",[["list"]]]]]]]]],"_fndef":true,"_fnparams":["Ele"]}]]]],"_fndef":true,"_fnparams":["Base","List","Handler","Generators","Filter"]}],["export-global","lcomp/3","lcomp/2"],["def","reverse",{"code":[[["next","reverse","L",["list"]]]],"_fndef":true,"_fnparams":["L"]}],["def","reverse",{"code":[[["if",["==","0",["length","L"]],[["Acc"]],["else",[["recurse",["tail","L"],["++",["list",["head","L"]],"Acc"]]]]]]],"_fndef":true,"_fnparams":["L","Acc"]}],["export-global","reverse/1"],["def","zip",{"code":[[["zip","A","B",["list"]]]],"_fndef":true,"_fnparams":["A","B"]}],["def","zip",{"code":[[["if",["or",["==","0",["length","A"]],["==","0",["length","B"]]],[["Acc"]],["else",[["recurse",["tail","A"],["tail","B"],["++","Acc",["list",["tuple",["head","A"],["head","B"]]]]]]]]]],"_fndef":true,"_fnparams":["A","B","Acc"]}],["export-global","zip/2"],["if",["==","true",["get-def","'TEST'"]],[["var","SampleList",["list","1","2","4","8","16","32"]],["print","\"Each test: \"",["each","SampleList",{"code":[[["print","N"]]],"_fndef":true,"_fnparams":["N"]}]],["print","\"Each-idx test: \"",["each-idx","SampleList",{"code":[[["print",["++","\"\"","I","\": \"","N"]]]],"_fndef":true,"_fnparams":["N","I"]}]],["print","\"Map test: \"",["map","SampleList",{"code":[[["*","N","2"]]],"_fndef":true,"_fnparams":["N"]}]],["print","\"Foldl test: \"",["foldl","SampleList","0",{"code":[[["+","N","A"]]],"_fndef":true,"_fnparams":["N","A"]}]],["print","\"Foldl test: \"",["foldl","SampleList","0",{"code":[[["<<","N","A"]]],"_fndef":true,"_fnparams":["N","A"]}]],["print","\"Empty map test: \"",["map",["list"],{"code":[[["*","N","2"]]],"_fndef":true,"_fnparams":["N"]}]],["print","\"Empty foldl test:\"",["foldl",["list"],"0",{"code":[[["+","N","A"]]],"_fndef":true,"_fnparams":["N","A"]}]],["each","SampleList",{"code":[[["print","\"N:\"","N"]]],"_fndef":true,"_fnparams":["N"]}],["print","\"Seq test:\"",["seq","1","5"]],["print","\"Reverse seq test:\"",["seq","5","1"]],["print","\"Sum test:\"",["sum","SampleList"]],["print","\"Prod test:\"",["prod","SampleList"]],["print","\"Permutations test: \"",["permutations",["list","1","2","3"]]],["print","\"Max test:\"",["max","10","5","9","4","8","3","6","2","1","0"]],["print","\"Min test:\"",["min","10","5","9","4","8","3","6","2","1","0"]],["print","\"Filter test:\"",["filter",["seq","1","10"],{"code":[["==","0",["@","V","2"]]],"_fndef":true,"_fnparams":["V"]}]],["var","Generators",["list",["seq","1","10"],["seq","1","5"],["seq","1","3"]]],["var","Handler",{"code":[["list",["list","X","Y","Z"]]],"_fndef":true,"_fnparams":["X","Y","Z"]}],["var","Filter",{"code":[[["and",["==","0",["@","X","2"]],["==","0",["@","Y","2"]],["==","0",["@","Z","2"]]]]],"_fndef":true,"_fnparams":["X","Y","Z"]}],["print","\"List comprehension test: \"",["lcomp","Handler","Generators","Filter"]],["print","\"Reverse test: \"",["reverse","SampleList"]],["print","\"Zip test: \"",["zip",["list","a","b","c","d"],["list","1","2","3","4"]]]]]]]
},{}],31:[function(require,module,exports){
module.exports = "% Provide functions working with lists.\n(\n\t(if (get-def 'NATIVE') (\n\t\t(print \"Using NATIVE lists functions\")\n\t))\n\n\t(if (get-def 'NATIVE') (\n\t\t%% @doc Map a list with a callback.\n\t\t%% @param List     list     elements to map\n\t\t%% @param Callback #V::any  callback function. returns a value\n\t\t%% @return list    List of transformed elements\n\t\t%% @builtin        Builtin for speed reasons.\n\t\t%% @condtional     NATIVE\n\t\t%% @cond-show      Use native function instead of builtin.\n\t\t(def map #List,Callback :: (\n\t\t\t(map-inner (list) List Callback)\n\t\t))\n\t))\n\n\t(def map-inner #Acc,List,Callback :: (\n\t\t(if (== 0 (length List)) (\n\t\t\t(Acc)\n\t\t) (else (\n\t\t\t(recurse (++ Acc (list (call Callback (head List)))) (tail List) Callback)\n\t\t)))\n\t))\n\n\t%% @doc Fold a list left with an initial value and return the final value.\n\t%% @param List           list  elements to fold\n\t%% @param Current=Initial any  initial value\n\t%% @param Callback       #Element,Accumulator::any\n\t%% @return Current\n\t(def foldl #List,Current,Callback :: (\n\t\t(if (== 0 (length List)) (\n\t\t\t(Current)\n\t\t) (else (\n\t\t\t(recurse (tail List) (call Callback (head List) Current) Callback)\n\t\t)))\n\t))\n\n\t%% @doc Similar to map but always returns nil.\n\t%% @param List           list  elements to fold\n\t%% @param Current=Initial any  initial value\n\t%% @param Callback       #Element,Index::any\n\t%% @return nil\n\t(def each #List,Callback :: (\n\t\t(each-inner 0 List Callback)\n\t))\n\n\t(def each-inner #Idx,List,Callback :: (\n\t\t(if (== 0 (length List)) (\n\t\t\t(atom nil)\n\t\t) (else (\n\t\t\t(call Callback (head List) Idx)\n\t\t\t(recurse (+ Idx 1) (tail List) Callback)\n\t\t)))\n\t))\n\n\t% Alias\n\t%% @see each/2\n\t(def each-idx #List,Callback :: ((each List Callback)))\n\n\t(export-global each/2 each-idx/2)\n\n\t%% @see seq/3\n\t(def seq #N0,N1 :: (\n\t\t(seq N0 N1 (? (< N0 N1) 1 -1))\n\t))\n\n\t%% @doc Sequence. Count from N0 to N1.\n\t%% @param N0   number  Number to start from\n\t%% @param N1   number  Number to count to\n\t%% @param Inc  number  Increment per number\n\t%% @return list[N0...N1]\n\t(def seq #N0,N1,Inc :: (\n\t\t(set L (list))\n\t\t(var N (get N0))\n\t\t(while ((if (>= Inc 1) ((<= N N1)) ((>= N N1)))) (\n\t\t\t(set L (++ L (list N)))\n\t\t\t(set N (+ N Inc))\n\t\t))\n\t\tL\n\t))\n\n\t(export-global map/2 foldl/3 each/2 seq/2 seq/3)\n\n\t(if (get-def 'NATIVE') (\n\t\t(var PermutationsPossibilities (list 0 1 2 6 24 120 720 5040 40320 362880 3628800 39916800 479001600))\n\n\t\t%% @doc Get all permutations of the given List.\n\t\t%% @param List   list  elements for permutations\n\t\t%% @return list  all   permutations for given List\n\t\t% Based on code from: http://stackoverflow.com/questions/9960908/permutations-in-javascript/37580979#37580979\n\t\t% Implements [Heap's method](http://homepage.math.uiowa.edu/~goodman/22m150.dir/2007/Permutation%20Generation%20Methods.pdf)\n\t\t(def permutations #List :: (\n\t\t\t(var Length (length List))\n\t\t\t(var Result (list-fill (index PermutationsPossibilities Length) 0))\n\t\t\t(var C (list-fill Length 0))\n\t\t\t(var I 1)\n\t\t\t(var J 1)\n\t\t\t(index-set Result 0 (slice List))\n\t\t\t(while ((< I Length)) (\n\t\t\t\t(var CI (index C I))\n\t\t\t\t(if (< CI I) (\n\t\t\t\t\t(var K (? (@ I 2) (get CI) 0))\n\t\t\t\t\t(var P (index List I))\n\t\t\t\t\t(index-set List I (index List K))\n\t\t\t\t\t(index-set List K P)\n\t\t\t\t\t(index-set C I (+ 1 CI))\n\t\t\t\t\t(set I 1)\n\t\t\t\t\t(index-set Result J (slice List))\n\t\t\t\t\t(set J (+ 1 (get J)))\n\t\t\t\t) (else (\n\t\t\t\t\t(index-set C I 0)\n\t\t\t\t\t(set I (+ 1 (get I)))\n\t\t\t\t)))\n\t\t\t))\n\t\t\t(get Result)\n\t\t))\n\t\t(export-global permutations/1)\n\t))\n\n\t%% @doc Calculate sum of given list\n\t%% @param L=List   list  elements to sum up\n\t%% @return number\n\t(def sum #L :: ((foldl L 0 #N,A :: ((+ N A)))))\n\n\t%% @doc Calculate product of given list\n\t%% @param L=List   list  elements to calculate product of\n\t%% @return number\n\t(def prod #L :: ((foldl L 1 #N,A :: ((* A N)))))\n\t(export-global sum/1 prod/1)\n\n\t%% @doc Filter a list using a predicate.\n\t%% @param List       list        elements\n\t%% @param Predicate  #Ele::bool  Predicate function\n\t%% @return list\n\t(def filter #List,Predicate :: (\n\t\t(filter-inner List Predicate (list))\n\t))\n\t(def filter-inner #List,Predicate,Acc :: (\n\t\t(if (== 0 (length List)) (\n\t\t\t(Acc)\n\t\t) (else (\n\t\t\t(var Ele (head List))\n\t\t\t(if (call Predicate Ele) (\n\t\t\t\t(recurse (tail List) Predicate (++ Acc (list Ele)))\n\t\t\t) (else (\n\t\t\t\t(recurse (tail List) Predicate Acc)\n\t\t\t)))\n\t\t)))\n\t))\n\n\t(export-global filter/2)\n\n\t%% @doc Get the maximum value from a given list.\n\t%%      Handles multiple stack lists.\n\t%% @param   List   list[number]  List of numbers. Automatically flattened.\n\t%% @return  number               The maximum value found.\n\t(def max/* #List :: (\n\t\t(set List (flatten List))\n\t\t(foldl (tail List) (head List) #V,A :: ((? (> V A) V A)))\n\t))\n\n\t%% @doc Get the minimum value from a given list.\n\t%%      Handles multiple stack lists.\n\t%% @param   List   list[number]  List of numbers. Automatically flattened.\n\t%% @return  number               The minimum value found.\n\t(def min/* #List :: (\n\t\t(set List (flatten List))\n\t\t(foldl (tail List) (head List) #V,A :: ((? (< V A) V A)))\n\t))\n\n\t(export-global min/* max/*)\n\n\t(if (get-def 'NATIVE') (\n\t\t%% @doc Perform a flat map of the given List with Callback.\n\t\t%% @param   List      list[E->any]  List of values to map.\n\t\t%% @param   Callback  fun(E)::E     Mapping callback function.\n\t\t%% @return  Flat map of the list.\n\t\t%%\n\t\t%% @example\n\t\t%%\n\t\t%%    (print \"Flat map:\" (flat-map (list 0 1 2 3 4 5) #X :: (\n\t\t%%        (list X (+ X 1))\n\t\t%%    )))\n\t\t%%\n\t\t%%  Output:\n\t\t%%    Flat map: [0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6]\n\t\t%% @end\n\t\t%% @builtin        Moved to builtins for speed reasons\n\t\t%% @conditional    NATIVE\n\t\t%% @cond-show      Use native function instead of builtin.\n\t\t(def flat-map #List,Callback :: (\n\t\t\t(apply ++ (++ (list) (map List Callback)))\n\t\t))\n\t))\n\n\t%% @doc List comprehension.\n\t%% @param Handler     #/*::*     A function that accepts the same number of arguments\n\t%%                               as the number of generators.\n\t%% @param Generators  list(list,...)     Generators, ie list of values.\n\t%% @param Filter      #/*::bool  A function that accepts the same number of arguments\n\t%%                               as the number of generators. Returns boolean.\n\t%% @return A new list with comprehended input\n\t(def lcomp #Handler,Generators,Filter :: (\n\t\t(lcomp-inner (list) (head Generators) Handler (tail Generators) Filter)\n\t))\n\n\t%% @see lcomp/3\n\t(def lcomp #Handler,Generators :: (\n\t\t(lcomp Handler Generators # :: ((atom true)))\n\t))\n\n\t%% @private\n\t%% @doc Performs the inner list comprehension.\n\t%%      If further generators are present, this function is called recursively\n\t%%      until no generators are left.\n\t%%      At that point, Filter is called and if successful returns Callback of\n\t%%      values.\n\t(def lcomp-inner #Base,List,Handler,Generators,Filter :: (\n\t\t(flat-map List (scope #Ele :: (\n\t\t\t(var Current (++ Base (list Ele)))\n\t\t\t(if (> (length Generators) 0) (\n\t\t\t\t(lcomp-inner Current (head Generators) Handler (tail Generators) Filter)\n\t\t\t) (else (\n\t\t\t\t(if (apply Filter Current) (\n\t\t\t\t\t(list (apply Handler Current))\n\t\t\t\t) (else (\n\t\t\t\t\t(list)\n\t\t\t\t)))\n\t\t\t)))\n\t\t)))\n\t))\n\n\t(export-global lcomp/3 lcomp/2)\n\n\t(def reverse #L :: ((next reverse L (list))))\n\t(def reverse #L,Acc :: (\n\t\t(if (== 0 (length L)) (\n\t\t\t(Acc)\n\t\t) (else (\n\t\t\t(recurse (tail L) (++ (list (head L)) Acc))\n\t\t)))\n\t))\n\n\t(export-global reverse/1)\n\n\t(def zip #A,B :: ((zip A B (list))))\n\t(def zip #A,B,Acc :: (\n\t\t(if (or (== 0 (length A)) (== 0 (length B))) (\n\t\t\t(Acc)\n\t\t) (else (\n\t\t\t(recurse (tail A) (tail B) (++ Acc (list (tuple (head A) (head B)))))\n\t\t)))\n\t))\n\t(export-global zip/2)\n\n\t% Pass -DTEST to livium.lithp to enable.\n\t(if (== true (get-def 'TEST')) (\n\t\t(var SampleList (list 1 2 4 8 16 32))\n\t\t(print \"Each test: \" (each SampleList #N :: ((print N))))\n\t\t(print \"Each-idx test: \" (each-idx SampleList #N,I :: ((print (++ \"\" I \": \" N)))))\n\t\t(print \"Map test: \" (map SampleList #N :: ((* N 2))))\n\t\t(print \"Foldl test: \" (foldl SampleList 0 #N,A :: ((+ N A))))\n\t\t(print \"Foldl test: \" (foldl SampleList 0 #N,A :: ((<< N A))))\n\t\t(print \"Empty map test: \" (map (list) #N :: ((* N 2))))\n\t\t(print \"Empty foldl test:\" (foldl (list) 0 #N,A :: ((+ N A))))\n\t\t(each SampleList #N :: (\n\t\t\t(print \"N:\" N)\n\t\t))\n\t\t(print \"Seq test:\" (seq 1 5))\n\t\t(print \"Reverse seq test:\" (seq 5 1))\n\t\t(print \"Sum test:\" (sum SampleList))\n\t\t(print \"Prod test:\" (prod SampleList))\n\t\t(print \"Permutations test: \" (permutations (list 1 2 3)))\n\t\t(print \"Max test:\" (max 10 5 9 4 8 3 6 2 1 0))\n\t\t(print \"Min test:\" (min 10 5 9 4 8 3 6 2 1 0))\n\t\t(print \"Filter test:\" (filter (seq 1 10) #V :: (== 0 (@ V 2))))\n\t\t(var Generators (list (seq 1 10) (seq 1 5) (seq 1 3)))\n\t\t(var Handler #X,Y,Z::(list (list X Y Z)))\n\t\t(var Filter #X,Y,Z::((and (== 0 (@ X 2)) (== 0 (@ Y 2)) (== 0 (@ Z 2)))))\n\t\t(print \"List comprehension test: \" (lcomp Handler Generators Filter))\n\t\t(print \"Reverse test: \" (reverse SampleList))\n\t\t(print \"Zip test: \" (zip (list a b c d) (list 1 2 3 4)))\n\t))\n\n)\n";

},{}],32:[function(require,module,exports){
module.exports=[[["def","true",{"code":[[["atom","true"]]],"_fndef":true,"_fnparams":[]}],["def","false",{"code":[[["atom","false"]]],"_fndef":true,"_fnparams":[]}],["export-global","true/0","false/0"],["def","is-number",{"code":[[["==","number",["typeof","V"]]]],"_fndef":true,"_fnparams":["V"]}],["def","is-string",{"code":[[["==","string",["typeof","V"]]]],"_fndef":true,"_fnparams":["V"]}],["def","is-function",{"code":[[["==","function",["typeof","V"]]]],"_fndef":true,"_fnparams":["V"]}],["def","is-function",{"code":[[["if",["is-function","V"],[["==","Arity",["function-arity","V"]]],["else",[["atom","false"]]]]]],"_fndef":true,"_fnparams":["V","Arity"]}],["def","is-list",{"code":[[["==","list",["typeof","V"]]]],"_fndef":true,"_fnparams":["V"]}],["def","is-atom",{"code":[[["==","atom",["typeof","V"]]]],"_fndef":true,"_fnparams":["V"]}],["def","is-dict",{"code":[[["==","dict",["typeof","V"]]]],"_fndef":true,"_fnparams":["V"]}],["def","is-tuple",{"code":[[["==","tuple",["typeof","V"]]]],"_fndef":true,"_fnparams":["V"]}],["export-global","is-number/1","is-string/1","is-function/1","is-function/2","is-list/1","is-atom/1","is-dict/1","is-tuple/1"],["def","when/*",{"code":[[["when-inner","Handlers"]]],"_fndef":true,"_fnparams":["Handlers"]}],["def","when-inner",{"code":[[["var","Handler",["head","Handlers"]],["var","Test",["index","Handler","0"]],["var","Success",["index","Handler","1"]],["var","TestResult","false"],["if",["is-atom","Test"],[["set","TestResult",["get","Test"]]],["else",[["if",["is-function","Test"],[["set","TestResult",["call","Test"]]],["else",[["throw","\"Unknown test given in when/*\""]]]]]]],["if",["==","true","TestResult"],[["call","Success"]],["else",[["if",[">",["length","Handlers"],"1"],[["recurse",["tail","Handlers"]]],["else",[["throw","\"No matching clause in when\""]]]]]]]]],"_fndef":true,"_fnparams":["Handlers"]}],["export-global","when/*"],["if",["get-def","'MATCH_TEST'"],[["import","assert"],["assert",["is-number","1"],"\"is-number integer check\""],["assert",["is-number","1.00"],"\"is-number float check\""],["assert",["is-string","\"A\""],"\"is-string check\""],["assert",["is-list",["list"]],"\"is-list check\""],["assert",["is-atom","atom"],"\"is-atom check\""],["assert",["is-function",["scope",{"code":[[["1"]]],"_fndef":true,"_fnparams":[]}]],"\"is-function check\""],["assert",["is-function",["scope",{"code":[[["1"]]],"_fndef":true,"_fnparams":["A","B","C"]}],"3"],"\"is-function #/3 check\""],["assert",["is-dict",["dict"]],"\"is-dict check\""],["assert",["is-tuple",["tuple"]],"\"is-tuple check\""],["def","test",{"code":[[["when",["tuple",["scope",{"code":[[["is-string","What"]]],"_fndef":true,"_fnparams":[]}],["scope",{"code":[[["atom","string"]]],"_fndef":true,"_fnparams":[]}]],["tuple",["scope",{"code":[[["is-function","What"]]],"_fndef":true,"_fnparams":[]}],["scope",{"code":[[["atom","function"]]],"_fndef":true,"_fnparams":[]}]],["tuple",["scope",{"code":[[["is-list","What"]]],"_fndef":true,"_fnparams":[]}],["scope",{"code":[[["atom","list"]]],"_fndef":true,"_fnparams":[]}]],["tuple",["scope",{"code":[[["is-atom","What"]]],"_fndef":true,"_fnparams":[]}],["scope",{"code":[[["atom","atom"]]],"_fndef":true,"_fnparams":[]}]],["tuple",["scope",{"code":[[["is-dict","What"]]],"_fndef":true,"_fnparams":[]}],["scope",{"code":[[["atom","dict"]]],"_fndef":true,"_fnparams":[]}]],["tuple",["scope",{"code":[[["is-number","What"]]],"_fndef":true,"_fnparams":[]}],["scope",{"code":[[["atom","number"]]],"_fndef":true,"_fnparams":[]}]]]]],"_fndef":true,"_fnparams":["What"]}],["assert",["==","number",["test","1"]],"\"when/* test: number\""],["assert",["==","string",["test","\"123\""]],"\"when/* test: string\""],["try",[["test",["tuple","foo"]],["throw","\"Uh oh\""]],{"code":[[["if",["==",["exception-message","E"],"\"No matching clause in when\""],[["atom","true"]],["else",[["throw","E"]]]]]],"_fndef":true,"_fnparams":["E"]}],["def","test-any",{"code":[[["when",["tuple","true",{"code":[[["\"PASS\""]]],"_fndef":true,"_fnparams":[]}]]]],"_fndef":true,"_fnparams":["What"]}],["assert",["==","\"PASS\"",["test-any","any"]],"\"when/* test: success path\""],["print","\"Match tests succeeded\""]]]]]
},{}],33:[function(require,module,exports){
module.exports = "(\n\t(def true  # :: ((atom true)))\n\t(def false # :: ((atom false)))\n\t(export-global true/0 false/0)\n\n\t% Pattern matching\n\t(def is-number #V :: ((== number (typeof V))))\n\t(def is-string #V :: ((== string (typeof V))))\n\t(def is-function #V :: ((== function (typeof V))))\n\t(def is-function #V,Arity :: (\n\t\t(if (is-function V) (\n\t\t\t(== Arity (function-arity V))\n\t\t) (else (\n\t\t\t(atom false)\n\t\t)))\n\t))\n\t(def is-list #V :: ((== list (typeof V))))\n\t(def is-atom #V :: ((== atom (typeof V))))\n\t(def is-dict #V :: ((== dict (typeof V))))\n\t(def is-tuple #V:: ((== tuple (typeof V))))\n\n\t(export-global is-number/1 is-string/1 is-function/1 is-function/2\n\t               is-list/1   is-atom/1   is-dict/1     is-tuple/1)\n\n\t(def when/* #Handlers :: (\n\t\t(when-inner Handlers)\n\t))\n\n\t(def when-inner #Handlers :: (\n\t\t(var Handler (head Handlers))\n\t\t(var Test (index Handler 0))\n\t\t(var Success (index Handler 1))\n\t\t(var TestResult false)\n\t\t(if (is-atom Test) (\n\t\t\t(set TestResult (get Test))\n\t\t) (else (\n\t\t\t(if (is-function Test) (\n\t\t\t\t(set TestResult (call Test))\n\t\t\t) (else (\n\t\t\t\t(throw \"Unknown test given in when/*\")\n\t\t\t)))\n\t\t)))\n\t\t(if (== true TestResult) (\n\t\t\t(call Success)\n\t\t) (else (\n\t\t\t(if (> (length Handlers) 1) (\n\t\t\t\t(recurse (tail Handlers))\n\t\t\t) (else (\n\t\t\t\t(throw \"No matching clause in when\")\n\t\t\t)))\n\t\t)))\n\t))\n\n\t(export-global when/*)\n\n\t(if (get-def 'MATCH_TEST') (\n\t\t(import assert)\n\t\t(assert (is-number 1)    \"is-number integer check\")\n\t\t(assert (is-number 1.00) \"is-number float check\")\n\t\t(assert (is-string \"A\")  \"is-string check\")\n\t\t(assert (is-list (list)) \"is-list check\")\n\t\t(assert (is-atom atom)   \"is-atom check\")\n\t\t(assert (is-function (scope # :: ((1)))) \"is-function check\")\n\t\t(assert (is-function (scope #A,B,C :: ((1))) 3) \"is-function #/3 check\")\n\t\t(assert (is-dict (dict)) \"is-dict check\")\n\t\t(assert (is-tuple (tuple)) \"is-tuple check\")\n\t\t(def test #What :: (\n\t\t\t(when\n\t\t\t\t(tuple (scope # :: ((is-string What)))   (scope # :: ((atom string))))\n\t\t\t\t(tuple (scope # :: ((is-function What))) (scope # :: ((atom function))))\n\t\t\t\t(tuple (scope # :: ((is-list What)))     (scope # :: ((atom list))))\n\t\t\t\t(tuple (scope # :: ((is-atom What)))     (scope # :: ((atom atom))))\n\t\t\t\t(tuple (scope # :: ((is-dict What)))     (scope # :: ((atom dict))))\n\t\t\t\t(tuple (scope # :: ((is-number What)))   (scope # :: ((atom number))))\n\t\t\t\t% Purposely do not include a \"true\" match to test that no match\n\t\t\t\t% throws an error.\n\t\t\t\t% Note that the is-tuple check is missing\n\t\t\t)\n\t\t))\n\n\t\t(assert (== number (test 1)) \"when/* test: number\")\n\t\t(assert (== string (test \"123\")) \"when/* test: string\")\n\t\t(try (\n\t\t\t(test (tuple foo))\n\t\t\t(throw \"Uh oh\")\n\t\t) #E :: (\n\t\t\t(if (== (exception-message E) \"No matching clause in when\") (\n\t\t\t\t% This is OK\n\t\t\t\t(atom true)\n\t\t\t) (else (\n\t\t\t\t(throw E)\n\t\t\t)))\n\t\t))\n\n\t\t% Unlike above test, this one will accept any given value because its\n\t\t% comparison function always returns true.\n\t\t(def test-any #What :: (\n\t\t\t(when (tuple true # :: ((\"PASS\"))))\n\t\t))\n\t\t(assert (== \"PASS\" (test-any any)) \"when/* test: success path\")\n\n\t\t(print \"Match tests succeeded\")\n\t))\n)\n";

},{}],34:[function(require,module,exports){
module.exports=[[["import","lists"],["var","ArityFuns",["dict",["tuple","1",["list","abs","acos","acosh","asin","asinh","atan","atanh","cbrt","ceil","clz32","cos","cosh","exp","expm1","floor","fround","log","log1p","log10","log2","round","sign","sin","sinh","sqrt","tan","tanh","trunc"]],["tuple","2",["list","atan2","imul","pow"]],["tuple","*",["list","hypot"]]]],["var","Math",["math-object"]],["each",["dict-keys","ArityFuns"],["scope",{"code":[[["var","Entries",["dict-get","ArityFuns","Arity"]],["each","Entries",["scope",{"code":[[["var","FullName",["atom",["+","Entry","\"/\"","Arity"]]],["if",["==","1","Arity"],[["def","FullName",["scope",{"code":[[["invoke","Math","Entry","A"]]],"_fndef":true,"_fnparams":["A"]}]],["export-global","FullName"]],["else",[["if",["==","2","Arity"],[["def","FullName",["scope",{"code":[[["invoke","Math","Entry","A","B"]]],"_fndef":true,"_fnparams":["A","B"]}]],["export-global","FullName"]],["else",[["if",["==","*","Arity"],[["def","FullName",["scope",{"code":[[["apply",["dict-get","Math","Entry"],"Args"]]],"_fndef":true,"_fnparams":["Args"]}]],["export-global","FullName"]]]]]]]]]]],"_fndef":true,"_fnparams":["Entry"]}]]]],"_fndef":true,"_fnparams":["Arity"]}]]]]
},{}],35:[function(require,module,exports){
module.exports = "(\n\t(import lists)\n\t(var ArityFuns (dict\n\t\t(tuple 1 (list abs   acos   acosh asin  asinh atan atanh\n\t\t               cbrt  ceil   clz32 cos   cosh  exp  expm1\n\t\t               floor fround log   log1p log10 log2 round\n\t\t               sign  sin    sinh  sqrt  tan   tanh trunc))\n\t\t(tuple 2 (list atan2 imul   pow))\n\t\t(tuple * (list hypot)) % Disabled: max    min))\n\t))\n\n\t(var Math (math-object))\n\t(each (dict-keys ArityFuns) (scope #Arity :: (\n\t\t(var Entries (dict-get ArityFuns Arity))\n\t\t(each Entries (scope #Entry :: (\n\t\t\t(var FullName (atom (+ Entry \"/\" Arity)))\n\t\t\t(if (== 1 Arity) (\n\t\t\t\t(def FullName (scope #A :: (\n\t\t\t\t\t(invoke Math Entry A)\n\t\t\t\t)))\n\t\t\t\t(export-global FullName)\n\t\t\t) (else (\n\t\t\t\t(if (== 2 Arity) (\n\t\t\t\t\t(def FullName (scope #A,B :: (\n\t\t\t\t\t\t(invoke Math Entry A B)\n\t\t\t\t\t)))\n\t\t\t\t\t(export-global FullName)\n\t\t\t\t) (else (\n\t\t\t\t\t(if (== * Arity) (\n\t\t\t\t\t\t(def FullName (scope #Args :: (\n\t\t\t\t\t\t\t(apply (dict-get Math Entry) Args)\n\t\t\t\t\t\t)))\n\t\t\t\t\t\t(export-global FullName)\n\t\t\t\t\t))\n\t\t\t\t)))\n\t\t\t)))\n\t\t)))\n\t)))\n)\n";

},{}],36:[function(require,module,exports){
module.exports=[[["import","lists"],["import","random"],["import","symbols"],["var","AttemptsDefault","50000"],["def","pivot",{"code":[[["var","Current","0"],["var","Result","nil"],["var","AttemptsRemaining",["get","AttemptsDefault"]],["var","LastPrintNum",["get","AttemptsRemaining"]],["var","I","0"],["var","Permutations",["permutations","Ops"]],["var","PermutationsLength",["length",["get","Permutations"]]],["while",[["and",["!=","Current","Desired"],[">","AttemptsRemaining","0"]]],[["var","OpsToTry",["index","Permutations","I"]],["set","I",["+","1",["get","I"]]],["if",[">=","I","PermutationsLength"],[["set","I","0"]]],["var","OpsPadded",["map",["tail","Nums"],["scope",{"code":[[["list-rand","OpsToTry"]]],"_fndef":true,"_fnparams":["N"]}]]],["var","Str","\"\""],["each-idx","Nums",["scope",{"code":[[["var","Op",["+","\"\"",["index","OpsPadded","Idx"]]],["if",["!=","\"\"","Op"],[["set","Str",["+","Str","\"(\"","Op","\" \"","N","\" \""]]],["else",[["set","Str",["+","Str","N","\")\""]]]]]]],"_fndef":true,"_fnparams":["N","Idx"]}]],["set","Str",["+","Str",["repeat","\")\"",["length","Nums"]]]],["set","Current",["eval","Str"]],["if",["==","Current","Desired"],[["set","Result",["get","Str"]]]],["set","AttemptsRemaining",["-","AttemptsRemaining","1"]],["if",[">=",["-","LastPrintNum","AttemptsRemaining"],"100"],[["set","LastPrintNum",["get","AttemptsRemaining"]],["invoke",["stdout"],"write",["+","\"\\r\"","LastPrintNum"]]]]]],["invoke",["stdout"],"write","\"...Success:\\n\""],["get","Result"]]],"_fndef":true,"_fnparams":["Desired","Nums","Ops"]}],["export-global","pivot/3"],["if",["get-def","'PIVOT_TEST'"],[["var","Numbers",["list","1","5","2","2"]],["var","Operators",["list","*","+"]],["var","Desired","20"],["print",["pivot","Desired","Numbers","Operators"]],["set","Numbers",["list","0","1","2","4","8","16","32"]],["set","Operators",["list","+","*","-","/","|","^"]],["print",["pivot","63","Numbers","Operators"]],["print",["pivot","64","Numbers","Operators"]]]]]]
},{}],37:[function(require,module,exports){
module.exports = "% Module: pivot\n%\n% Pivot a mathematical expression to reach a desired output.\n%\n% Example: (pivot 63 (list 0 1 2 4 8 16 32) (list + * - / | ^))\n%  Yields: (^ 0 (^ 1 (| 2 (+ 4 (| 8 (+ 16 32))))))))\n%\n(\n\t(import lists)\n\t(import random)\n\t(import symbols)\n\n\t(var AttemptsDefault 50000)\n\n\t(def pivot #Desired,Nums,Ops :: (\n\t\t(var Current 0)\n\t\t(var Result nil)\n\t\t(var AttemptsRemaining (get AttemptsDefault))\n\t\t(var LastPrintNum (get AttemptsRemaining))\n\t\t(var I 0)\n\t\t(var Permutations (permutations Ops))\n\t\t(var PermutationsLength (length (get Permutations)))\n\t\t(while ((and (!= Current Desired) (> AttemptsRemaining 0))) (\n\t\t\t(var OpsToTry (index Permutations I))\n\t\t\t(set I (+ 1 (get I)))\n\t\t\t(if (>= I PermutationsLength) (\n\t\t\t\t(set I 0)\n\t\t\t))\n\t\t\t(var OpsPadded (map (tail Nums) (scope #N :: ((list-rand OpsToTry)))))\n\t\t\t(var Str \"\")\n\t\t\t(each-idx Nums (scope #N,Idx :: (\n\t\t\t\t(var Op (+ \"\" (index OpsPadded Idx)))\n\t\t\t\t(if (!= \"\" Op) (\n\t\t\t\t\t(set Str (+ Str \"(\" Op \" \" N \" \"))\n\t\t\t\t) (else (\n\t\t\t\t\t(set Str (+ Str N \")\"))\n\t\t\t\t)))\n\t\t\t)))\n\t\t\t(set Str (+ Str (repeat \")\" (length Nums))))\n\t\t\t(set Current (eval Str))\n\t\t\t(if (== Current Desired) (\n\t\t\t\t(set Result (get Str))\n\t\t\t))\n\t\t\t(set AttemptsRemaining (- AttemptsRemaining 1))\n\t\t\t(if (>= (- LastPrintNum AttemptsRemaining) 100) (\n\t\t\t\t(set LastPrintNum (get AttemptsRemaining))\n\t\t\t\t(invoke (stdout) write (+ \"\\r\" LastPrintNum))\n\t\t\t))\n\t\t))\n\t\t(invoke (stdout) write \"...Success:\\n\")\n\t\t(get Result)\n\t))\n\n\t(export-global pivot/3)\n\n\t(if (get-def 'PIVOT_TEST') (\n\t\t(var Numbers (list 1 5 2 2))\n\t\t(var Operators (list * +))\n\t\t(var Desired 20) % 1 * 5 * 2 + 2\n\t\t(print (pivot Desired Numbers Operators))\n\t\t(set Numbers (list 0 1 2 4 8 16 32))\n\t\t(set Operators (list + * - / | ^ ))\n\t\t% << >> | ^ / -))\n\t\t(print (pivot 63 Numbers Operators))\n\t\t(print (pivot 64 Numbers Operators))\n\t))\n)\n";

},{}],38:[function(require,module,exports){
module.exports=[[["var","DefaultMin","0"],["var","DefaultMax","1000000"],["def","random",{"code":[[["random","DefaultMin","DefaultMax"]]],"_fndef":true,"_fnparams":[]}],["def","random",{"code":[[["random","0","End"]]],"_fndef":true,"_fnparams":["End"]}],["def","random",{"code":[[["+","Start",["floor",["*",["rand"],["-","End","Start"]]]]]],"_fndef":true,"_fnparams":["Start","End"]}],["export","random/0","random/1","random/2"],["def","random-list-item",{"code":[[["index","List",["random",["length","List"]]]]],"_fndef":true,"_fnparams":["List"]}],["export","random-list-item/1"],["if",["get-def","'TEST'"],[["print",["random"]],["print",["random","10"]],["print",["random","1","10"]],["print",["random","1","100"]],["print",["random-list-item",["list","1","2","3","4","5","6","7"]]]]]]]
},{}],39:[function(require,module,exports){
module.exports = "% Provide integer random numbers\n(\n\t(var DefaultMin 0)\n\t(var DefaultMax 1000000)\n\t(def random # :: ((random DefaultMin DefaultMax)))\n\t(def random #End :: ((random 0 End)))\n\t(def random #Start,End :: (\n\t\t(+ Start (floor (* (rand) (- End Start))))\n\t))\n\t(export random/0 random/1 random/2)\n\n\t(def random-list-item #List :: (\n\t\t(index List (random (length List)))\n\t))\n\t(export random-list-item/1)\n\n\t(if (get-def 'TEST') (\n\t\t(print (random))\n\t\t(print (random 10))\n\t\t(print (random 1 10))\n\t\t(print (random 1 100))\n\t\t(print (random-list-item (list 1 2 3 4 5 6 7)))\n\t))\n)\n";

},{}],40:[function(require,module,exports){
module.exports=[[["if",["==",["host"],"\"Node.js\""],[["try",[["var","Readline",["require","\"readline\""]],["var","RL",["invoke","Readline","\"createInterface\"",["dict",["tuple","input",["stdin"]],["tuple","output",["stdout"]]]]],["invoke","RL","pause"],["def","readline",{"code":[[["invoke","RL","\"question\"","Question",["js-bridge",{"code":[[["invoke","RL","\"pause\""],["call","Callback","Answer"]]],"_fndef":true,"_fnparams":["Answer"]}]]]],"_fndef":true,"_fnparams":["Question","Callback"]}],["export-global","readline/2"]],["catch",{"code":[[["atom","nil"]]],"_fndef":true,"_fnparams":[]}]],["if",["==","true",["get-def","'TEST'"]],[["readline","\"How are you? \"",{"code":[[["print","A"],["readline","\"How are you really? \"",{"code":[[["print","B"]]],"_fndef":true,"_fnparams":["B"]}]]],"_fndef":true,"_fnparams":["A"]}]]]],["else",[["if",["==",["host"],"\"browser\""],[["print","\"readline: browser hack\""],["import","html-toolkit"],["def","readline",{"code":[[["htmlOnLoad",["scope",{"code":[[["prompt","Question","Callback"]]],"_fndef":true,"_fnparams":[]}]]]],"_fndef":true,"_fnparams":["Question","Callback"]}],["export-global","readline/2"]]]]]]]]
},{}],41:[function(require,module,exports){
module.exports = "% Provide Readline functionality from standard NodeJS library.\n(\n\t(if (== (host) \"Node.js\") (\n\t\t(try (\n\t\t\t(var Readline (require \"readline\"))\n\t\t\t(var RL (invoke Readline \"createInterface\" (dict\n\t\t\t\t\t(tuple input (stdin))\n\t\t\t\t\t(tuple output (stdout))\n\t\t\t\t))\n\t\t\t)\n\t\t\t(invoke RL pause)\n\n\t\t\t(def readline #Question,Callback :: (\n\t\t\t\t(invoke RL \"question\" Question (js-bridge #Answer :: (\n\t\t\t\t\t(invoke RL \"pause\")\n\t\t\t\t\t(call Callback Answer)\n\t\t\t\t)))\n\t\t\t))\n\t\t\t(export-global readline/2)\n\t\t) (catch # :: (\n\t\t\t(atom nil)\n\t\t)))\n\n\t\t(if (== true (get-def 'TEST')) (\n\t\t\t(readline \"How are you? \" #A :: (\n\t\t\t\t(print A)\n\t\t\t\t(readline \"How are you really? \" #B :: (\n\t\t\t\t\t(print B)\n\t\t\t\t))\n\t\t\t))\n\t\t))\n\t) (else (\n\t\t(if (== (host) \"browser\") (\n\t\t\t(print \"readline: browser hack\")\n\t\t\t(import html-toolkit)\n\t\t\t(def readline #Question,Callback :: (\n\t\t\t\t(htmlOnLoad (scope # :: (\n\t\t\t\t\t(prompt Question Callback)\n\t\t\t\t)))\n\t\t\t))\n\t\t\t(export-global readline/2)\n\t\t))\n\t)))\n)\n";

},{}],42:[function(require,module,exports){
module.exports=[[["import","readline"],["import","stderr"],["import","switch"],["var","ContinueLoop","true"],["var","_","nil"],["var","DebugMode","false"],["var","Result","nil"],["def","nil",{"code":[[["atom","\"nil\""]]],"_fndef":true,"_fnparams":[]}],["def","local-eval",["scope",{"code":[[["if","DebugMode",[["lithp-debug","true"]]],["set","E",["eval","Code"]],["if","DebugMode",[["lithp-debug","false"]]],["get","E"]]],"_fndef":true,"_fnparams":["Code"]}]],["var","CaseQuit",["case","\"\\\\q\"",["scope",{"code":[[["set","ContinueLoop","false"],["nil"]]],"_fndef":true,"_fnparams":[]}]]],["var","CaseUnderscore",["case","\"_\"",["scope",{"code":[["get","_"]],"_fndef":true,"_fnparams":[]}]]],["var","CaseDebugMode",["case","\"\\\\d\"",["scope",{"code":[[["set","DebugMode",["!",["get","DebugMode"]]],["print","\"Debug mode now \"",["?","DebugMode","\"ON\"","\"off\""]],["nil"]]],"_fndef":true,"_fnparams":[]}]]],["var","DisplayHelp",{"code":[[["print","\"Type standard Lithp expressions.\""],["print","\"Example: (var Fac #N::((if(== 0 N)((1))((* N(call Fac(- N 1)))))))(print (call Fac 10\""],["print","\"Or for a recursive factorial:\""],["print","\"((def f #N :: ( (def fi #N,A :: ( (if (== 1 N) ((A)) (else ((recurse (- N 1) (* N A)))) ) )) (fi N 1) )) (print (f 10)) )\""],["print","\"\""],["print","\"The following additional commands are available:\""],["print","\"  ?        Print this help\""],["print","\"  \\\\q       Quit the REPL\""],["print","\"  \\\\d       Toggle DEBUG mode\""],["print","\"  _        Print the last value\""],["print","\"\""],["nil"]]],"_fndef":true,"_fnparams":[]}],["var","CaseHelp1",["case","\"?\"","DisplayHelp"]],["var","CaseHelp2",["case","\"help\"","DisplayHelp"]],["var","CaseDefault",["default",["scope",{"code":[[["set-top-level","true"],["try",[["local-eval",["+","\"(\"","Input","\")\""]]],{"code":[[["stderr-write",["+","\"\\nError during eval: \"",["to-string","E"],"\"\\n\""]]]],"_fndef":true,"_fnparams":["E"]}]]],"_fndef":true,"_fnparams":["Input"]}]]],["var","CaseList",["list","CaseQuit","CaseUnderscore","CaseDebugMode","CaseHelp1","CaseHelp2","CaseDefault"]],["def","repl-input",["scope",{"code":[[["var","Tmp",["switch","Input","CaseList"]],["set","Result",["get","Tmp"]],["print","\"Success, result: \"","Result"],["set","\"_\"",["get","Result"]],["set-top-level","false"]]],"_fndef":true,"_fnparams":["Input"]}]],["export-global","repl-input/1"],["var","LoopHandler",["scope",{"code":[[["repl-input","Input"],["repl-loop"]]],"_fndef":true,"_fnparams":["Input"]}]],["def","repl-loop",["scope",{"code":[[["if","ContinueLoop",[["readline","\"> \"","LoopHandler"]]]]],"_fndef":true,"_fnparams":[]}]],["def","set-repl-continue",["scope",{"code":[[["set","ContinueLoop",["get","Bool"]]]],"_fndef":true,"_fnparams":["Bool"]}]],["export-global","repl-loop/0","set-repl-continue/1"]]]
},{}],43:[function(require,module,exports){
module.exports = "% Module: REPL\n%\n% Provides a Read Execute Print Loop, allowing for an interactive interface.\n%\n% Currently only single lines are supported.\n%\n(\n\t(import readline)\n\t(import stderr)\n\t(import switch)\n\n\t(var ContinueLoop true)\n\t(var _ nil)\n\t(var DebugMode false)\n\t(var Result nil)\n\n\t(def nil # :: ((atom \"nil\")))\n\n\t(def local-eval (scope #Code :: (\n\t\t(if DebugMode (\n\t\t\t(lithp-debug true)\n\t\t))\n\t\t(set E (eval Code))\n\t\t(if DebugMode (\n\t\t\t(lithp-debug false)\n\t\t))\n\t\t(get E)\n\t)))\n\n\t(var CaseQuit (case \"\\\\q\" (scope # :: ((set ContinueLoop false)(nil)))))\n\t(var CaseUnderscore (case \"_\" (scope # :: (get _))))\n\t(var CaseDebugMode (case \"\\\\d\" (scope # :: (\n\t\t(set DebugMode (! (get DebugMode)))\n\t\t(print \"Debug mode now \" (? DebugMode \"ON\" \"off\"))\n\t\t(nil)\n\t))))\n\t(var DisplayHelp # :: (\n\t\t(print \"Type standard Lithp expressions.\")\n\t\t(print \"Example: (var Fac #N::((if(== 0 N)((1))((* N(call Fac(- N 1)))))))(print (call Fac 10\")\n\t\t(print \"Or for a recursive factorial:\")\n\t\t(print \"((def f #N :: ( (def fi #N,A :: ( (if (== 1 N) ((A)) (else ((recurse (- N 1) (* N A)))) ) )) (fi N 1) )) (print (f 10)) )\")\n\t\t(print \"\")\n\t\t(print \"The following additional commands are available:\")\n\t\t(print \"  ?        Print this help\")\n\t\t(print \"  \\\\q       Quit the REPL\")\n\t\t(print \"  \\\\d       Toggle DEBUG mode\")\n\t\t(print \"  _        Print the last value\")\n\t\t(print \"\")\n\t\t(nil)\n\t))\n\t(var CaseHelp1 (case \"?\" DisplayHelp))\n\t(var CaseHelp2 (case \"help\" DisplayHelp))\n\n\t(var CaseDefault (default (scope #Input :: (\n\t\t(set-top-level true)\n\t\t(try (\n\t\t\t(local-eval (+ \"(\" Input \")\"))\n\t\t) #E :: (\n\t\t\t(stderr-write (+ \"\\nError during eval: \" (to-string E) \"\\n\"))\n\t\t))\n\t))))\n\n\t(var CaseList (list CaseQuit CaseUnderscore CaseDebugMode CaseHelp1\n\t                    CaseHelp2 CaseDefault))\n\n\t(def repl-input (scope #Input :: (\n\t\t(var Tmp (switch Input CaseList))\n\t\t(set Result (get Tmp))\n\t\t(print \"Success, result: \" Result)\n\t\t(set \"_\" (get Result))\n\t\t(set-top-level false)\n\t)))\n\t(export-global repl-input/1)\n\n\t(var LoopHandler (scope #Input :: (\n\t\t(repl-input Input)\n\t\t(repl-loop)\n\t)))\n\n\t(def repl-loop (scope # :: (\n\t\t(if ContinueLoop (\n\t\t\t(readline \"> \" LoopHandler)\n\t\t))\n\t)))\n\n\t(def set-repl-continue (scope #Bool :: (\n\t\t(set ContinueLoop (get Bool))\n\t)))\n\n\t(export-global repl-loop/0 set-repl-continue/1)\n)\n";

},{}],44:[function(require,module,exports){
module.exports=[[["if",["==",["host"],"\"Node.js\""],[["def","stderr-write",{"code":[[["invoke",["stderr"],"write","V"]]],"_fndef":true,"_fnparams":["V"]}],["export-global","stderr-write/1"]],["else",[["def","stderr-write",{"code":[[["print","\"STDERR: \"","V"]]],"_fndef":true,"_fnparams":["V"]}],["export-global","stderr-write/1"]]]]]]
},{}],45:[function(require,module,exports){
module.exports = "(\n\t(if (== (host) \"Node.js\") (\n\t\t(def stderr-write #V :: ((invoke (stderr) write V)))\n\t\t(export-global stderr-write/1)\n\t) (else (\n\t\t(def stderr-write #V :: ((print \"STDERR: \" V)))\n\t\t(export-global stderr-write/1)\n\t)))\n)\n";

},{}],46:[function(require,module,exports){
module.exports=[[["var","Modules",["list","assert","bignum","buffer","cache","class","file","lists","math","match","pivot","random","readline","switch","stream","symbols"]],["def","import-modules",{"code":[[["if",["!=","0",["length","List"]],[["try",[["import",["head","List"]]],["catch",{"code":[[["print","\"Failed to import \"",["head","List"]]]],"_fndef":true,"_fnparams":[]}]],["recurse",["tail","List"]]]]]],"_fndef":true,"_fnparams":["List"]}],["import-modules","Modules"]]]
},{}],47:[function(require,module,exports){
module.exports = "(\n\t(var Modules (list\n\t\tassert       % Assertion functions\n\t\tbignum       % \n\t\tbuffer       % Provide some buffer-related functions\n\t\tcache        % Function result cache\n\t\tclass        % Very basic class module\n\t\tfile         % File IO\n\t\tlists        % List related functions\n\t\tmath         % Math functions\n\t\tmatch\n\t\tpivot\n\t\trandom       % Random number functions\n\t\treadline     % \n\t\tswitch       % The classic switch function\n\t\tstream\n\t\tsymbols      % Symbol functions\n\t))\n\t(def import-modules #List :: (\n\t\t(if (!= 0 (length List)) (\n\t\t\t(try (\n\t\t\t\t(import (head List))\n\t\t\t) (catch # :: (\n\t\t\t\t(print \"Failed to import \" (head List))\n\t\t\t)))\n\t\t\t(recurse (tail List))\n\t\t))\n\t))\n\t(import-modules Modules)\n)\n";

},{}],48:[function(require,module,exports){
module.exports=[[["try",[["import","buffer"],["var","FS",["require","\"fs\""]],["def","isTTY",{"code":[[["?",["==",["true"],["index",["stdin"],"isTTY"]],"true","false"]]],"_fndef":true,"_fnparams":["Stream"]}],["def","readInputStream",{"code":[[["if",["isTTY",["stdin"]],[["\"\""]],["else",[["read-stream-to-buffer",["stdin"]]]]]]],"_fndef":true,"_fnparams":[]}],["def","stream-fd",{"code":[[["index","Stream","fd"]]],"_fndef":true,"_fnparams":["Stream"]}],["var","InputInitialized","false"],["def","input-init",["scope",{"code":[[["if",["!","InputInitialized"],[["invoke",["stdin"],"setRawMode",["true"]],["set","InputInitialized","true"]]]]],"_fndef":true,"_fnparams":[]}]],["def","readInputStreamByte",{"code":[[["input-init"],["var","Buf",["buffer","1"]],["invoke",["stdin"],"resume"],["invoke","FS","readSync",["stream-fd",["stdin"]],"Buf","0","1"],["invoke",["stdin"],"pause"],["to-string","Buf",["null"],"0","1"]]],"_fndef":true,"_fnparams":[]}],["export-global","readInputStreamByte/0"],["def","writeOutputStreamByte",{"code":[[["invoke","FS","write",["stream-fd",["stdout"]],"C"]]],"_fndef":true,"_fnparams":["C"]}],["def","getc",{"code":[[["readInputStreamByte"]]],"_fndef":true,"_fnparams":[]}],["def","putc",{"code":[[["writeOutputStreamByte","C"]]],"_fndef":true,"_fnparams":["C"]}],["export-global","getc/0","putc/1"],["var","BufferSize","256"],["def","read-stream-to-buffer",{"code":[[["var","Result","\"\""],["var","BytesRead","1"],["var","Buf",["buffer","BufferSize"]],["while",[[">","BytesRead","0"]],[["set","BytesRead","0"],["try",[["set","BytesRead",["invoke","FS","readSync",["stream-fd","Stream"],"Buf","0","BufferSize"]],["set","Result",["+","Result",["to-string","Buf",["null"],"0","BytesRead"]]]],{"code":[[["atom","nil"]]],"_fndef":true,"_fnparams":["E"]}]]],["get","Result"]]],"_fndef":true,"_fnparams":["Stream"]}],["export-global","isTTY/1","stream-fd/1","read-stream-to-buffer/1","readInputStream/0"]],["catch",{"code":[[["print","\"Error loading stream: \"","E"],["print","\"stream module unavailable\""]]],"_fndef":true,"_fnparams":["E"]}]]]]
},{}],49:[function(require,module,exports){
module.exports = "% Module: stream\n%\n% Provides functions for working with streams.\n(\n\t(try (\n\t\t(import buffer)\n\n\t\t(var FS (require \"fs\"))\n\n\t\t(def isTTY #Stream :: (\n\t\t\t(? (== (true) (index (stdin) isTTY)) true false)\n\t\t))\n\n\t\t(def readInputStream # :: (\n\t\t\t(if (isTTY (stdin)) (\n\t\t\t\t(\"\")\n\t\t\t) (else (\n\t\t\t\t(read-stream-to-buffer (stdin))\n\t\t\t)))\n\t\t))\n\n\t\t(def stream-fd #Stream :: ((index Stream fd)))\n\n\t\t(var InputInitialized false)\n\n\t\t(def input-init (scope # :: (\n\t\t\t(if (! InputInitialized) (\n\t\t\t\t(invoke (stdin) setRawMode (true))\n\t\t\t\t(set InputInitialized true)\n\t\t\t))\n\t\t)))\n\n\t\t(def readInputStreamByte # :: (\n\t\t\t(input-init)\n\t\t\t(var Buf (buffer 1))\n\t\t\t(invoke (stdin) resume)\n\t\t\t(invoke FS readSync (stream-fd (stdin)) Buf 0 1)\n\t\t\t(invoke (stdin) pause)\n\t\t\t(to-string Buf (null) 0 1)\n\t\t))\n\t\t(export-global readInputStreamByte/0)\n\n\t\t(def writeOutputStreamByte #C :: (\n\t\t\t(invoke FS write (stream-fd (stdout)) C)\n\t\t))\n\n\t\t(def getc # :: ((readInputStreamByte)))\n\t\t(def putc #C :: ((writeOutputStreamByte C)))\n\n\t\t(export-global getc/0 putc/1)\n\n\t\t(var BufferSize 256)\n\n\t\t(def read-stream-to-buffer #Stream :: (\n\t\t\t(var Result \"\")\n\t\t\t(var BytesRead 1)\n\t\t\t(var Buf (buffer BufferSize))\n\t\t\t(while ((> BytesRead 0)) (\n\t\t\t\t(set BytesRead 0)\n\t\t\t\t(try (\n\t\t\t\t\t(set BytesRead (invoke FS readSync (stream-fd Stream) Buf 0 BufferSize))\n\t\t\t\t\t(set Result (+ Result (to-string Buf (null) 0 BytesRead)))\n\t\t\t\t) #E :: (\n\t\t\t\t\t(atom nil)\n\t\t\t\t))\n\t\t\t))\n\t\t\t(get Result)\n\t\t))\n\n\t\t(export-global isTTY/1 stream-fd/1 read-stream-to-buffer/1 readInputStream/0)\n\t) (catch #E :: (\n\t\t(print \"Error loading stream: \" E)\n\t\t(print \"stream module unavailable\")\n\t)))\n)\n";

},{}],50:[function(require,module,exports){
module.exports=[[["def","concat/*",{"code":[[["var","Result","\"\""],["map","List",["scope",{"code":[[["set","Result",["+","Result",["+","\" \"","Str"]]]]],"_fndef":true,"_fnparams":["Str"]}]],["get","Result"]]],"_fndef":true,"_fnparams":["List"]}],["export-global","concat/*"]]]
},{}],51:[function(require,module,exports){
module.exports = "(\n\t% Concatenate strings (or objects that can be added to strings, such as\n\t% numbers.)\n\t(def concat/* #List :: (\n\t\t(var Result \"\")\n\t\t(map List (scope #Str :: (\n\t\t\t(set Result (+ Result (+ \" \" Str)))\n\t\t)))\n\t\t(get Result)\n\t))\n\t(export-global concat/*)\n)\n";

},{}],52:[function(require,module,exports){
module.exports=[[["def","true",{"code":[["atom","true"]],"_fndef":true,"_fnparams":[]}],["def","false",{"code":[["atom","false"]],"_fndef":true,"_fnparams":[]}],["export-global","true/0","false/0"],["def","case",{"code":[[["scope",{"code":[[["if",["==","Given","Value"],[["tuple","ok",["call","Action"]]],["else",[["tuple","false","false"]]]]]],"_fndef":true,"_fnparams":["Given"]}]]],"_fndef":true,"_fnparams":["Value","Action"]}],["def","default",{"code":[[["scope",{"code":[[["tuple","default",["call","Action","Given"]]]],"_fndef":true,"_fnparams":["Given"]}]]],"_fndef":true,"_fnparams":["Action"]}],["def","switch",{"code":[[["var","Result","nil"],["var","ResultSet","false"],["var","DefaultValue","nil"],["while",[["and",["!","ResultSet"],[">",["length","Handlers"],"0"]]],[["var","Head",["head","Handlers"]],["var","Tail",["tail","Handlers"]],["set","Handlers",["get","Tail"]],["var","InnerResult",["call","Head","Value"]],["if",["==","ok",["index","InnerResult","0"]],[["set","Result",["index","InnerResult","1"]],["set","ResultSet","true"]],["else",[["if",["==","default",["index","InnerResult","0"]],[["set","DefaultValue",["index","InnerResult","1"]]]]]]]]],["?","ResultSet","Result","DefaultValue"]]],"_fndef":true,"_fnparams":["Value","Handlers"]}],["def","switch/*",{"code":[[["switch",["head","Args"],["tail","Args"]]]],"_fndef":true,"_fnparams":["Args"]}],["if",["==","true",["get-def","'TEST'"]],[["print","\"Debug is on, running tests\""],["var","Case1",["case","1",{"code":[["\"one\""]],"_fndef":true,"_fnparams":[]}]],["var","Case2",["case","2",{"code":[["\"two\""]],"_fndef":true,"_fnparams":[]}]],["var","Case3",["case","3",{"code":[["\"three\""]],"_fndef":true,"_fnparams":[]}]],["var","Case4",["case","4",{"code":[["\"four\""]],"_fndef":true,"_fnparams":[]}]],["var","Default",["default",{"code":[[["+","\"Other: \"","Given"]]],"_fndef":true,"_fnparams":["Given"]}]],["var","Value","1"],["print",["switch","Value","Case1","Case2","Case3","Case4","Default"]],["print",["switch","Value",["list",["case","1",{"code":[["\"one\""]],"_fndef":true,"_fnparams":[]}],["case","2",{"code":[["\"two\""]],"_fndef":true,"_fnparams":[]}],["case","3",{"code":[["\"three\""]],"_fndef":true,"_fnparams":[]}],["case","4",{"code":[["\"four\""]],"_fndef":true,"_fnparams":[]}],["default",{"code":[[["+","\"Other: \"","N"]]],"_fndef":true,"_fnparams":["N"]}]]]]]],["export-global","case/2","default/1","switch/2","switch/*"]]]
},{}],53:[function(require,module,exports){
module.exports = "% Implements the standard switch construct in Lithp.\n%\n% Usage:\n%\n%  (switch Value Handlers)\n%\n% Where:\n%\n%  Value         is any value to compare\n%  Handlers      is a (list) of handlers.\n%\n% Available handlers:\n%\n%  (case Value,Action#::)    If switch value is Value, perform Action.\n%                            Note that no arguments are given to Action.\n%  (default Action#Value::)  If no matches found, this action is performed.\n%                            It is given the value passed to switch.\n(\n\t% A parsing error presently prevents the following atoms from being\n\t% parsed correctly. We instead make functions for them that return\n\t% the atoms.\n\t(def true # :: (atom true))\n\t(def false # :: (atom false))\n\t(export-global true/0 false/0)\n\t(def case #Value,Action :: (\n\t\t(scope #Given :: (\n\t\t\t(if (== Given Value) ((tuple ok (call Action)))\n\t\t\t    (else ((tuple false false)))\n\t\t\t)\n\t\t))\n\t))\n\t(def default #Action :: (\n\t\t(scope #Given :: (\n\t\t\t(tuple default (call Action Given))\n\t\t))\n\t))\n\t(def switch #Value,Handlers :: (\n\t\t(var Result nil)\n\t\t(var ResultSet false)\n\t\t(var DefaultValue nil)\n\t\t(while ((and (! ResultSet) (> (length Handlers) 0))) (\n\t\t\t(var Head (head Handlers))\n\t\t\t(var Tail (tail Handlers))\n\t\t\t(set Handlers (get Tail))\n\t\t\t(var InnerResult (call Head Value))\n\t\t\t(if (== ok (index InnerResult 0)) (\n\t\t\t\t(set Result (index InnerResult 1))\n\t\t\t\t(set ResultSet true)\n\t\t\t) (else (\n\t\t\t\t(if (== default (index InnerResult 0)) (\n\t\t\t\t\t(set DefaultValue (index InnerResult 1))\n\t\t\t\t))\n\t\t\t)))\n\t\t))\n\t\t(? ResultSet Result DefaultValue)\n\t))\n\t(def switch/* #Args :: (\n\t\t(switch (head Args) (tail Args))\n\t))\n\n\t% To enable this section, pass -DTEST to run.js\n\t(if (== true (get-def 'TEST')) (\n\t\t(print \"Debug is on, running tests\")\n\t\t(var Case1 (case 1 # :: (\"one\")))\n\t\t(var Case2 (case 2 # :: (\"two\")))\n\t\t(var Case3 (case 3 # :: (\"three\")))\n\t\t(var Case4 (case 4 # :: (\"four\")))\n\t\t(var Default (default #Given :: ((+ \"Other: \" Given))))\n\t\t(var Value 1)\n\t\t(print (switch Value Case1 Case2 Case3 Case4 Default))\n\t\t(print (switch Value (list\n\t\t\t(case 1 # :: (\"one\"))\n\t\t\t(case 2 # :: (\"two\"))\n\t\t\t(case 3 # :: (\"three\"))\n\t\t\t(case 4 # :: (\"four\"))\n\t\t\t(default #N :: ((+ \"Other: \" N)))\n\t\t)))\n\t))\n\t(export-global case/2 default/1 switch/2 switch/*)\n)\n";

},{}],54:[function(require,module,exports){
module.exports=[[["def","get-fn",{"code":[[["try",[["get",["+","Name","\"/\"","Arity"]]],{"code":[[["get",["+","Name","\"/*\""]]]],"_fndef":true,"_fnparams":["E"]}]]],"_fndef":true,"_fnparams":["Name","Arity"]}],["export-global","get-fn/2"],["def","call-fn",{"code":[[["call",["get-fn","Name","1"],"Arg1"]]],"_fndef":true,"_fnparams":["Name","Arg1"]}],["def","call-fn",{"code":[[["call",["get-fn","Name","2"],"Arg1","Arg2"]]],"_fndef":true,"_fnparams":["Name","Arg1","Arg2"]}],["def","call-fn",{"code":[[["call",["get-fn","Name","3"],"Arg1","Arg2","Arg3"]]],"_fndef":true,"_fnparams":["Name","Arg1","Arg2","Arg3"]}],["def","call-fn",{"code":[[["call",["get-fn","Name","4"],"Arg1","Arg2","Arg3","Arg4"]]],"_fndef":true,"_fnparams":["Name","Arg1","Arg2","Arg3","Arg4"]}],["def","call-fn",{"code":[[["call",["get-fn","Name","5"],"Arg1","Arg2","Arg3","Arg4","Arg5"]]],"_fndef":true,"_fnparams":["Name","Arg1","Arg2","Arg3","Arg4","Arg5"]}],["def","call-fn",{"code":[[["call",["get-fn","Name","6"],"Arg1","Arg2","Arg3","Arg4","Arg5","Arg6"]]],"_fndef":true,"_fnparams":["Name","Arg1","Arg2","Arg3","Arg4","Arg5","Arg6"]}],["def","call-fn",{"code":[[["call",["get-fn","Name","7"],"Arg1","Arg2","Arg3","Arg4","Arg5","Arg6","Arg7"]]],"_fndef":true,"_fnparams":["Name","Arg1","Arg2","Arg3","Arg4","Arg5","Arg6","Arg7"]}],["export-global","call-fn/2","call-fn/3","call-fn/4","call-fn/5","call-fn/6","call-fn/7","call-fn/8"],["if",["get-def","'TEST'"],[["import","lists"],["var","Operators",["list","+","-","/","*"]],["var","A","5"],["var","B","10"],["each","Operators",["scope",{"code":[[["var","Fn",["get-fn","Op","2"]],["print",["+","A","\" \"","Op","\" \"","B","\" = \"",["call","Fn","A","B"]]]]],"_fndef":true,"_fnparams":["Op"]}]],["each","Operators",["scope",{"code":[[["print",["+","A","\" \"","Op","\" \"","B","\" = \"",["call-fn","Op","A","B"]]]]],"_fndef":true,"_fnparams":["Op"]}]]]]]]
},{}],55:[function(require,module,exports){
module.exports = "% Module: symbols\n%\n% Provides functions for getting and calling currently defined symbols.\n% Symbols include functions and variables.\n(\n\t%% Get a function by name and arity\n\t%% If given arity is not found, checks for arity *.\n\t%% If arity * function also not found, exception is thrown.\n\t(def get-fn #Name,Arity :: (\n\t\t(try (\n\t\t\t(get (+ Name \"/\" Arity))\n\t\t) #E :: (\n\t\t\t(get (+ Name \"/*\"))\n\t\t))\n\t))\n\t(export-global get-fn/2)\n\n\t%% @for=call-fn/?\n\t%% Call a function by name with the given arguments.\n\t(def call-fn #Name,Arg1 :: ((call (get-fn Name 1) Arg1)))\n\t(def call-fn #Name,Arg1,Arg2 :: ((call (get-fn Name 2) Arg1 Arg2)))\n\t(def call-fn #Name,Arg1,Arg2,Arg3 :: ((call (get-fn Name 3) Arg1 Arg2 Arg3)))\n\t(def call-fn #Name,Arg1,Arg2,Arg3,Arg4 :: ((call (get-fn Name 4) Arg1 Arg2 Arg3 Arg4)))\n\t(def call-fn #Name,Arg1,Arg2,Arg3,Arg4,Arg5 :: ((call (get-fn Name 5) Arg1 Arg2 Arg3 Arg4 Arg5)))\n\t(def call-fn #Name,Arg1,Arg2,Arg3,Arg4,Arg5,Arg6 :: (\n\t\t(call (get-fn Name 6) Arg1 Arg2 Arg3 Arg4 Arg5 Arg6)\n\t))\n\t(def call-fn #Name,Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7 :: (\n\t\t(call (get-fn Name 7) Arg1 Arg2 Arg3 Arg4 Arg5 Arg6 Arg7)\n\t))\n\t(export-global call-fn/2 call-fn/3 call-fn/4 call-fn/5 call-fn/6 call-fn/7 call-fn/8)\n\n\t(if (get-def 'TEST') (\n\t\t(import lists)\n\t\t(var Operators (list + - / *))\n\t\t(var A 5)\n\t\t(var B 10)\n\t\t(each Operators (scope #Op :: (\n\t\t\t(var Fn (get-fn Op 2))\n\t\t\t(print (+ A \" \" Op \" \" B \" = \" (call Fn A B)))\n\t\t)))\n\t\t(each Operators (scope #Op :: (\n\t\t\t(print (+ A \" \" Op \" \" B \" = \" (call-fn Op A B)))\n\t\t)))\n\t))\n)\n";

},{}],56:[function(require,module,exports){
module.exports={
  "_args": [
    [
      {
        "raw": "lithp@git+https://github.com/andrakis/node-lithp.git",
        "scope": null,
        "escapedName": "lithp",
        "name": "lithp",
        "rawSpec": "git+https://github.com/andrakis/node-lithp.git",
        "spec": "git+https://github.com/andrakis/node-lithp.git",
        "type": "hosted",
        "hosted": {
          "type": "github",
          "ssh": "git@github.com:andrakis/node-lithp.git",
          "sshUrl": "git+ssh://git@github.com/andrakis/node-lithp.git",
          "httpsUrl": "git+https://github.com/andrakis/node-lithp.git",
          "gitUrl": "git://github.com/andrakis/node-lithp.git",
          "shortcut": "github:andrakis/node-lithp",
          "directUrl": "https://raw.githubusercontent.com/andrakis/node-lithp/master/package.json"
        }
      },
      "/home/daedalus/git/lithp-webide/node_modules/lithp-pkg"
    ]
  ],
  "_from": "git+https://github.com/andrakis/node-lithp.git",
  "_id": "lithp@0.30.0",
  "_inCache": true,
  "_location": "/lithp",
  "_phantomChildren": {},
  "_requested": {
    "raw": "lithp@git+https://github.com/andrakis/node-lithp.git",
    "scope": null,
    "escapedName": "lithp",
    "name": "lithp",
    "rawSpec": "git+https://github.com/andrakis/node-lithp.git",
    "spec": "git+https://github.com/andrakis/node-lithp.git",
    "type": "hosted",
    "hosted": {
      "type": "github",
      "ssh": "git@github.com:andrakis/node-lithp.git",
      "sshUrl": "git+ssh://git@github.com/andrakis/node-lithp.git",
      "httpsUrl": "git+https://github.com/andrakis/node-lithp.git",
      "gitUrl": "git://github.com/andrakis/node-lithp.git",
      "shortcut": "github:andrakis/node-lithp",
      "directUrl": "https://raw.githubusercontent.com/andrakis/node-lithp/master/package.json"
    }
  },
  "_requiredBy": [
    "/lithp-pkg"
  ],
  "_resolved": "git+https://github.com/andrakis/node-lithp.git#b4d55bceab5be76f90d0a010512f8f7552331d22",
  "_shasum": "a9b5c512bb12e3dbf0f6a95642c5bb17d5542a78",
  "_shrinkwrap": null,
  "_spec": "lithp@git+https://github.com/andrakis/node-lithp.git",
  "_where": "/home/daedalus/git/lithp-webide/node_modules/lithp-pkg",
  "author": {
    "name": "Julian \"Andrakis\" Thatcher"
  },
  "bin": {
    "lithp": "bin/lithp",
    "lithp-repl": "bin/repl",
    "lithp-macro": "bin/macro"
  },
  "bugs": {
    "url": "https://github.com/andrakis/node-lithp/issues"
  },
  "dependencies": {},
  "description": "A small Lisp-like language with a tiny interpreter",
  "devDependencies": {},
  "gitHead": "b4d55bceab5be76f90d0a010512f8f7552331d22",
  "homepage": "https://github.com/andrakis/node-lithp#readme",
  "keywords": [
    "lisp",
    "lithp"
  ],
  "license": "GPL-3.0",
  "main": "index.js",
  "name": "lithp",
  "optionalDependencies": {},
  "readme": "Lithp\n=====\n\nA small Lisp-like programming language, with a small interpreter.\n-----------------------------------------------------------------\n\nThis language borrows some ideas from Lisp (functional programming, the\nfunction call syntax itself) but is designed around a small interpreter to\ncarry out the basic execution, and builtin library functions to provide\ncontrol flow, function definitions, and basic arithmatic and similar\noperations.\n\nIt aims to provide a basic framework as powerful as JavaScript. Much of this\nis accomplished through the use of native Lithp [modules](https://github.com/andrakis/node-lithp/tree/master/modules)\nand some powerful builtin functions allowing use of native Node.js modules.\n\nAn online [web IDE](http://andrakis.github.io/ide2/) is available for running Lithp code in your browser. Parts of the web IDE are written in Lithp.\n\nThe [main interpreter](https://github.com/andrakis/node-lithp/blob/master/lib/interpreter.js) is around 270 lines of sparse code.\nThis size would be even lower without the\ndebug statements and detailed comments.\n\nLanguage Examples\n=================\n\nMore examples are in the [samples](https://github.com/andrakis/node-lithp/tree/master/samples) directory.\n\nSimple test\n-----------\n\nPrint a string.\n\n\t((set Test \"test\")\n\t (print \"Test: \" Test))\n\n[Try it online!](https://andrakis.github.io/lithp-webide/?code=JSBQcmludCBhIHN0cmluZy4KKAogICAgKHNldCBUZXN0ICJ0ZXN0IikKICAgIChwcmludCAiVGVzdDogIiBUZXN0KQopCg==)\n\nSimple function\n---------------\n\nDefine a simple function and call it.\n\n\t((def add #A,B :: ((+ A B)))\n\t (print \"Add 5+10: \" (add 5 10)))\n\n[Try it online!](https://andrakis.github.io/lithp-webide/?code=JSBEZWZpbmUgYSBzaW1wbGUgZnVuY3Rpb24gYW5kIGNhbGwgaXQuCigKICAgIChkZWYgYWRkICNBLEIgOjogKCgrIEEgQikpKQogICAgKHByaW50ICJBZGQgNSsxMDogIiAoYWRkIDUgMTApKQopCg==)\n\nMultiple functions and logic\n----------------------------\n\nDefine two functions and use comparison logic to print a message\nbased on the input.\n\n\t(\n\t\t(def is_zero #N :: ((== 0 N)))\n\t\t(def test #N :: (\n\t\t\t(if (is_zero N) (\n\t\t\t\t(print \"N is zero\")\n\t\t\t) (else (\n\t\t\t\t(print \"N is not zero, it is: \" N)\n\t\t\t)))\n\t\t))\n\t\t(test 1)\n\t\t(test 0)\n\t)\n\n[Try it online!](https://andrakis.github.io/lithp-webide/?code=JSBEZWZpbmUgdHdvIGZ1bmN0aW9ucyBhbmQgdXNlIGNvbXBhcmlzb24gbG9naWMgdG8gcHJpbnQgYSBtZXNzYWdlCiUgYmFzZWQgb24gdGhlIGlucHV0LgooCiAgICAoZGVmIGlzX3plcm8gI04gOjogKCg9PSAwIE4pKSkKICAgIChkZWYgdGVzdCAjTiA6OiAoCiAgICAgICAgKGlmIChpc196ZXJvIE4pICgKICAgICAgICAgICAgKHByaW50ICJOIGlzIHplcm8iKQogICAgICAgICkgKGVsc2UgKAogICAgICAgICAgICAocHJpbnQgIk4gaXMgbm90IHplcm8sIGl0IGlzOiAiIE4pCiAgICAgICAgKSkpCiAgICApKQogICAgKHRlc3QgMSkKICAgICh0ZXN0IDApCikK)\n\nA recursive function\n--------------------\n\nDefine a recursive function that calculates the factorial of the\ngiven number, and call it.\n\n\t((def fac #N :: (\n\t\t(if (== 0 N) (1)\n\t\t\t(else ((* N (fac (- N 1)))))\n\t\t)\n\t))\n\t(set Test 10)\n\t(print \"factorial of \" Test \": \" (fac Test)))\n\n[Try it online!](https://andrakis.github.io/lithp-webide/?code=JSBEZWZpbmUgYSByZWN1cnNpdmUgZnVuY3Rpb24gdGhhdCBjYWxjdWxhdGVzIHRoZSBmYWN0b3JpYWwgb2YgdGhlCiUgZ2l2ZW4gbnVtYmVyLCBhbmQgY2FsbCBpdC4KKAogICAgKGRlZiBmYWMgI04gOjogKAogICAgICAgIChpZiAoPT0gMCBOKSAoMSkKICAgICAgICAgICAgKGVsc2UgKCgqIE4gKGZhYyAoLSBOIDEpKSkpKQogICAgICAgICkKICAgICkpCiAgICAoc2V0IFRlc3QgMTApCiAgICAocHJpbnQgImZhY3RvcmlhbCBvZiAiIFRlc3QgIjogIiAoZmFjIFRlc3QpKQopCg==)\n\nA tail recursive function\n-------------------------\n\nTail recursion is implemented via the builtin recurse/* function.\n\n\t((def fac-recursive #N :: (\n\t\t(def inner #N,Acc :: (\n\t\t\t(if (== 0 N) (\n\t\t\t\t(Acc)\n\t\t\t) (else (\n\t\t\t\t(recurse (- N 1) (* N Acc))\n\t\t\t)))\n\t\t))\n\t\t(inner N 1)\n\t))\n\t(print (fac-recursive 50)))\n\n[Try it online!](https://andrakis.github.io/lithp-webide/?code=JSBUYWlsIHJlY3Vyc2lvbiBpcyBpbXBsZW1lbnRlZCB2aWEgdGhlIGJ1aWx0aW4gcmVjdXJzZS8qIGZ1bmN0aW9uLgooCiAgICAoZGVmIGZhYy1yZWN1cnNpdmUgI04gOjogKAogICAgICAgIChkZWYgaW5uZXIgI04sQWNjIDo6ICgKICAgICAgICAgICAgKGlmICg9PSAwIE4pICgKICAgICAgICAgICAgICAgIChBY2MpCiAgICAgICAgICAgICkgKGVsc2UgKAogICAgICAgICAgICAgICAgKHJlY3Vyc2UgKC0gTiAxKSAoKiBOIEFjYykpCiAgICAgICAgICAgICkpKQogICAgICAgICkpCiAgICAgICAgKGlubmVyIE4gMSkKICAgICkpCiAgICAocHJpbnQgKGZhYy1yZWN1cnNpdmUgNTApKQopCg==)\n\nList comprehension\n------------------\n\nList comprehension is provided by the `lists` module. Here is an example usage:\n\n\tCode:\n\t\t(import lists)\n\t\t% Supply 3 generators\n\t\t(set Generators (list (seq 1 10) (seq 1 5) (seq 1 3)))\n\t\t% Handler simply returns a list of given numbers\n\t\t(set Handler #X,Y,Z::((list X Y Z)))\n\t\t% Filter checks that X, Y, and Z are divisible by two using modulo (@).\n\t\t(set Filter #X,Y,Z::((and (== 0 (@ X 2)) (== 0 (@ Y 2)) (== 0 (@ Z 2)))))\n\t\t(print \"List comprehension test: \" (lcomp Handler Generators Filter))\n\tOutput:\n\t\tList comprehension test:  [ [ 2, 2, 2 ],\n\t\t  [ 2, 4, 2 ],\n\t\t  [ 4, 2, 2 ],\n\t\t  [ 4, 4, 2 ],\n\t\t  [ 6, 2, 2 ],\n\t\t  [ 6, 4, 2 ],\n\t\t  [ 8, 2, 2 ],\n\t\t  [ 8, 4, 2 ],\n\t\t  [ 10, 2, 2 ],\n\t\t  [ 10, 4, 2 ] ]\n\n[Try it online!](https://andrakis.github.io/lithp-webide/?code=JSBMaXN0IGNvbXByZWhlbnNpb24gaXMgcHJvdmlkZWQgYnkgdGhlIGBsaXN0c2AgbW9kdWxlLiBIZXJlIGlzIGFuIGV4YW1wbGUgdXNhZ2U6CigKICAgIChpbXBvcnQgbGlzdHMpCiAgICAlIFN1cHBseSAzIGdlbmVyYXRvcnMKICAgIChzZXQgR2VuZXJhdG9ycyAobGlzdCAoc2VxIDEgMTApIChzZXEgMSA1KSAoc2VxIDEgMykpKQogICAgJSBIYW5kbGVyIHNpbXBseSByZXR1cm5zIGEgbGlzdCBvZiBnaXZlbiBudW1iZXJzCiAgICAoc2V0IEhhbmRsZXIgI1gsWSxaOjooKGxpc3QgWCBZIFopKSkKICAgICUgRmlsdGVyIGNoZWNrcyB0aGF0IFgsIFksIGFuZCBaIGFyZSBkaXZpc2libGUgYnkgdHdvIHVzaW5nIG1vZHVsbyAoQCkuCiAgICAoc2V0IEZpbHRlciAjWCxZLFo6OigoYW5kICg9PSAwIChAIFggMikpICg9PSAwIChAIFkgMikpICg9PSAwIChAIFogMikpKSkpCiAgICAocHJpbnQgIkxpc3QgY29tcHJlaGVuc2lvbiB0ZXN0OiAiIChsY29tcCBIYW5kbGVyIEdlbmVyYXRvcnMgRmlsdGVyKSkKKQ==)\n\nRunning some sample code\n========================\n\nYou have four options:\n\n  * The online Web IDE\n\n     An [IDE capable of running Lithp code](https://andrakis.github.io/lithp-webide) directly is available.\n\n  * The online REPL\n\n     A REPL is [available online](https://andrakis.github.io/lithp/) that will run basic code snippits. This does not yet support running an entire script.\n\n  * The console REPL\n\n     The REPL, or Read Execute Print Loop, is available in the top level directory. To start it invoke:\n\n\t\t./repl          or\n\t\t./repl.lithp\n\n  * Run a script file\n\n     Use the file `run.js` in the top level directory, and specify a path to a Lithp\n     source file. There are [several provided](https://github.com/andrakis/node-lithp/tree/master/samples) that work with the current parser.\n\n    To run the [factorial example](https://github.com/andrakis/node-lithp/blob/master/samples/factorial.lithp):\n\n    ```\n        node run.js samples/factorial.lithp\n    ```\n\n    You can see the internals of what the parser and interpreter are doing by passing\n    the `-d` flag to run.js to enable debug mode. This prints out a tree of function\n    calls, allowing you to follow the interpreters call sequence.\n\nLanguage Status\n===============\n\nVersion: 0.30.0 (STABLE)\n---------------------\n\nA [web IDE](http://andrakis.github.io/ide2) is available for developing in your browswer. (A backup is also [available](https://andrakis.github.io/lithp-webide).)\n\nCurrently the language can run hand-compiled code or use the Bootstrap Parser\nfor a fairly feature-complete compilation experience. The parser does not\ncurrently supports all the constructs it should - these are being corrected\nas they are found.\n\nModules are supported, and a standard library is starting to be expanded upon.\nFor more information on modules, see the [module](https://github.com/andrakis/node-lithp/blob/master/samples/module.lithp) example for how functions may be defined, exported,\nand imported.\n\nSee `run.js` or the `Running some sample code` section for information on how\nto run existing examples of Lithp code, parsed by the Bootstrap Parser.\n\nThe Bootstrap Parser or Platform V0 Parser is written in JavaScript for\nquick implementation. See the `Longterm goals` section for information about\nthe design of a new parser, implemented in Lithp.\n\nThe Bootstrap Parser is very simple and will not protect you from simple mistakes\nlike too many closing brackets. It also gets tripped up over some slight syntax\nissues, but the basic framework implemented should allow for all of these to be\ncorrected.\n\nImplemented milestones\n----------------------\n\nListed in order of implementation, most recent first.\n\n* Speed improvements\n\n  * Since most functions are defined in the uppermost chain, including builtins, implements a new method of grabbing functions by defaulting\n    to the top chain.\n\n  * Updates how Lithp symbols are grabbed from closure, improving lookup speed.\n\n* Lithp in the browser\n\n  * [lithp-pkg](https://github.com/andrakis/lithp-pkg) has been used to package all of Lithp up into a set of files that browserify can use.\n\n  * [Online web IDE](https://andrakis.github.io/lithp-webide), developed using [lithp-webide](https://github.com/andrakis/lithp-webide).\n\n* Parsing\n\n  * Serialization of compiled OpChains to AST. Allows for other Lithp interpreters to run parsed code. (A C# interpreter is in progress.)\n\n  * AST parsing and compilation has been implemented.\n\n  * This allows faster script startup, and allows packaging the entire project using browserify.\n\n* Modules\n\n  * A list comprehension function, `lcomp`, is available in the [lists module](https://github.com/andrakis/node-lithp/blob/master/modules/lists.lithp)\n\n  * The same module also provides a flat-map function.\n\n  * Lists module has been improved with use of recursive functions.\n\n* REPL\n\n  * An online REPL is [available](https://andrakis.github.io/lithp/)\n\n  * A REPL is available for Node.js. Simply run `./repl` to start it. Type `?` for help.\n\n* Language enhancements\n\n  * Package the REPL using browserify to provide an online interpreter. (see [lithp-pkg](https://github.com/andrakis/lithp-pkg))\n\n  * Implemented `recurse/*`, enabling tail recursion.\n\n  * Implemented `while/2`, enabling non-recursive looping.\n\n  * The lists module has been rewritten to use `while/2`, resulting in much less\n    memory usage and improved runtime speed.\n\n  * Moved many functions from `Platform V1` to standard builtin library.\n\n  * Added many math builtins.\n\n  * Added missing regex test function (`test/2`)\n\n  * Added `env/0`, `argv/0`, `cwd/0` for command line information.\n\n  * Added number parsing: `parse-float/1`, `parse-int/1`\n\n  * Added `eval/1` allowing runtime code evaluation using the Bootstrap Parser.\n    Also adds `eval/*` for providing additional variables.\n\n  * Added `chr/1` and `asc/1` for converting to and from character codes and strings.\n\n* Debugging enhancements\n\n  * User defined functions now have a readable name, resulting in much more readable\n    debug output.\n\n  * The spacing and depth indications have been corrected and are now more consistent.\n\n  * No longer prints known symbol names when a symbol is not found. This was proving to\n    be too useless.\n\n* BootStrap Parser\n\n  * This basic parser, written in JavaScript, is able to convert scripts to the\n    OpChains the interpreter needs.\n\n  * It is designed to be powerful enough to parse enough Lithp code with which\n    to implement a better parser. To this end, there are numerous [examples](https://github.com/andrakis/node-lithp/tree/master/samples)\n    demonstrating the language and what the parser is capable of parsing.\n\n  * It is considered feature complete. Only bugfixes are to be implemented.\n\n  * Future parsing work is to be done on the Platform V1 parser, implemented\n    in Lithp and parsed by this parser. This should make maintenance and enhancements\n    easier to implement.\n\n  * Now recognises a number of builtin functions and saves runtime speed by resolving\n    these to arity star functions during parsing.\n\n  * Floating point numbers now work correctly, as does \\t escape sequence.\n\n  * Issues parsing tabs and newlines corrected.\n\n* Module system\n\n  * Allows scripts to import another module. Imported module is parsed by\n    the BootStrap parser and all functions run in their own instance of Lithp.\n\n  * A small standard library is provided. This is being expanded upon.\n\n  * Modules can define their own functions, call any function they want, and\n    export defined functions.\n\n  * Scripts that import modules add them to their function definition tree.\n\n  * Imported functions run in the new instance, retaining access to all their\n    own functions and variables.\n\n  * Scripts that call imported functions can be passed any Lithp object,\n    including anonymous functions.\n\n  * When passed anonymous functions will, like the imported module functions,\n    run in the instance of the interpreter in which they were defined. This\n    retains their access to all defined functions and variables.\n\n  * Enhanced import/1 to search a set of module paths, allowing for greater\n    flexibility.\n\n  * Several standard modules are now provided\n\n  * Added `import-instance/1` which retains the old behaviour of `import/1`.\n    `import/1` no longer imports modules into a new instance.\n\n* Speed improvements\n\n  * A number of enhancements have been made that improve the runtime speed\n    of the language. These include quicker name lookups, caching of arity\n    star functions once recognised, and strict mode.\n\n  * Strict mode is now implemented across all files.\n\nShort term goals\n----------------\n\n* Stackless interpreter - much faster and allowing infinite call depth. Based on a [paper on the implementation of Stackless Python](http://www.stackless.com/spcpaper.htm).\n\n* Web IDE Version 2 - a fully integrated IDE [[under development](https://andrakis.github.io/ide2/)].\n\n* Implement a Lithp package system with library dependancies.\n\n* Expand the standard module library.\n\n* The language is considered powerful enough and feature complete that\n  personal work has begun on new projects using Lithp as their base language. These are all works in progress.\n\n  * [Livium](https://github.com/andrakis/lithp-livium) - an implementation of Vi in Lithp.\n\n  * [Lithp-pkg](https://github.com/andrakis/lithp-pkg) - package Lithp into a browserified file.\n\n  * [Lithp-webide](https://github.com/andrakis/lithp-webide) - an IDE for the browser supporting Lithp.\n\n  * [Dungeons of Lithp](https://github.com/andrakis/lithp-dol) - a MUD-style dungeon crawler.\n\nLongterm goals\n--------------\n\nThese features are desired, but may be a long time coming.\n\n* Platform V1: Parser\n\n\tThe new native parser will feature more language features, including the ability\n\tto alter the parser itself at runtime, allowing completely new features to be\n\timplemented at runtime.\n\nDesign\n======\n\nThe basic syntax is very Lisp-like, however it has its own runtime library\nthat uses much different names, design, and implementation. For instance, the\nLithp code is broken down in OpChains, function calls, and literal values, and\nthese are interpreted to run the program. In comparison, Lisp implementations\noften use a low level virtual machine or compiles your code to an executable.\n\nIt also borrows some core ideas from Erlang:\n\n\t* Tuples:                       {val1, val2, ...}\n\t* Atoms:                        lowercase-Start-Is-Atom\n\t* Quoted Atoms:                 'A quoted atom'\n\t* Variables:                    StartWithUpperCase\n\t* Functions include arity:      (def add/2 #A,B :: ((+ A B)))\n\t                                Note that if not provided, this is\n\t                                automatically added according to the\n\t                                number of parameters the function takes.\n\t                                All functions in the definition table\n\t                                have the arity in their name.\n\t* Modules can export functions: (export add/2 divide/2)\n\t* Scripts can import modules:   (import \"lib\")\n\t                                Note that Erlang expects a list of function\n\t                                arity definitions for importing, whereas\n\t                                all exported functions are imported here.\n\n\nHowever, features such as destructive assignment are present, which differs\nfrom Erlang. A number of other useful features such as pattern matching,\nlist comprehension, binary buffers are implemented as modules.\n\nAdditionally, one may define functions with an arity of *, which\npasses all parameters in the first parameter:\n\n\t((def count_params/* #List :: ((print \"You gave me \" (length List) \" parameters\")))\n\t (count_params 1 2 3 atom \"string\" 'quoted atom' #N :: (\"anonymous function\")))\n\nOther features are available in many other languages. The prime one of these\nis the functional programming approach. All functions return the value of the\nlast executed function call, even if there are multiple function calls\npreceding it.\n\nAll Lithp functions are implemented as anonymous functions, which allows you\nto assign them to variables, provide them as function arguments, and call them\nusing the `call` function. The builtin `def` function adds anonymous functions\nto a closure table allowing them to be called at runtime by name. All builtins\nare also added to this table, making them indistuinguisable from user defined\nfunctions.\n\nVariable scoping (closures) is somewhat implemented, but none yet to liking.\nPresently, one needs to call the `scope/1` function. This takes an anonymous\nfunction as its parameter, and returns a callable function which retains\naccess to the scope in which it was defined. Ideally this would be implemented\nas a parser feature.\n\nA standard Lithp script compiles to an OpChain, which contains function calls,\nliteral values, and potentially more OpChains with the same.\n\nA simple program:\n\n\t((print \"Hello, world!\"))\n\nThis is an OpChain consisting of a single function call, with a single literal\nvalue as a parameter. Parameters are separated by spaces, and the function name\nappears as the first token after the opening bracket. Any function currently\ndefined by builtins or using the def/2 function is callable in this way.\n\nOther functions, such as those assigned to variables, must be called with the\ncall/* function.\n\nEach function call may itself have additional function calls for the values of\nthe parameters. These are parsed first, and this process repeats recursively\nuntil all parameters for the current function call have been resolved. This\nusually involves calling intermediate functions, which repeat the same process.\nThis is the meat of the language.\n\n\t ((def add #A,B :: ((+ A B)))\n\t  (print \"Add 5+10: \" (add 5 10)))\n\nThis simple design, consisting of only nested function calls and literal values,\nallows for a very simple interpreter that can implement powerful constructs.\n\nLithp functions are always anonymous, take a certain number of parameters (in\nthe above example, A and B), and assign this anonymous function to an atom in\nthe current closure, allowing it to be called like other inbuilt functions.\n\nWhen functions are set in the closure, they include in their name the arity of\nthe function. This is either a zero-or-positive-number, or * to indicate the\nfunction takes an unlimited number of parameters. In the case of arity * all\narguments are passed in the first parameter of the function.\n\nPrint itself is an arity * builtin runtime function defined in JavaScript.\nMost low level functions are provided in JavaScript, such as basic control\nflow, comparison, assignment and retrieval, and defining new functions in the\nLithp language itself.\n\nThe runtime library is fairly small, aiming for a very basic but usable\nset of functions that can implement most algorithms.\nMore advanced functionality is provided by additional libraries, such as\nwith Platform V1 which has functions for manipulating native Lithp types\n(for creating and filling OpChains.)\n\nSome functions are provided for readability, such as in an if construct:\n\n\t\t(if (== 0 N) (1)\n\t\t\t(else ((* N (fac (- N 1)))))\n\t\t)\n\nIn this case, else is just a function that calls the given function chain.\nIt could be ommitted, but it provides better readability in a language that\nis very terse.\n\nModules\n=======\n\nModules allow functions from one script to be exported to another script.\n\nAn example is provided, consisting of a [module](https://github.com/andrakis/node-lithp/blob/master/samples/module_lib.lithp) and a [script](https://github.com/andrakis/node-lithp/blob/master/samples/module.lithp) to call it.\n\nThe module is a standard Lithp script that contains calls to export/* to\nnote symbols to export:\n\n\t% lib.lithp\n\t((def add #A,B :: ((+ A B)))\n\t (export add/2))\n\nA different Lithp script may then use import/1 to bring all exported\ndefinitions into the running script's closure:\n\n\t% main.lithp\n\t((import \"lib\")\n\t (print \"2+2:\" (add 2 2)))\n\nHowever, a key point is that imported functions run in a different instance\nof the interpreter, allowing them to perform their own runtime logic completely\nindependent of the script that imported it.\n\nSince variables and function calls are resolved prior to calling a function, one\nmay call an imported function and provide it parameters and callbacks native to\nthe a different instance of the Lithp interpreter than the module.\n\nTo put it another way, module functions run in their own instance, but you can pass\nthem any usual value, including callbacks that retain access to defined values.\n\nSyntax Highlighting\n===================\n\nSee the directory `syntax` for Lithp syntax files.\n\nThe following syntax files are provided:\n\n* EditPlus\n\n   Standard EditPlus syntax file. Seems to work correctly.\n\n* VIM\n\n   Based upon the Lisp syntax file. The author's understanding of VIM syntax files\n   is not very good, hence it doesn't do everything correctly.\n",
  "readmeFilename": "README.md",
  "repository": {
    "type": "git",
    "url": "git+https://github.com/andrakis/node-lithp.git"
  },
  "scripts": {
    "postinstall": "if [ ! -L run ]; then ln -s run.js run; fi"
  },
  "version": "0.30.0"
}

},{}],57:[function(require,module,exports){
(function (global){
/**
 * Bootstrap Parser, Platform V0, for Lithp
 *
 * Main parser for the first version of Lithp. A simple parser that can be used
 * to create a better parser later (Platform V1).
 *
 * See 'run.js' (in the top level directory) for a working usage of this parser.
 */

"use strict";

var util = require('util'),
	inspect = util.inspect;
var lithp = require( './../../index'),
	Lithp = lithp.Lithp,
	parser_debug = lithp.parser_debug,
	types = lithp.Types,
	OpChain = types.OpChain,
	Atom = types.Atom,
	FunctionCall = types.FunctionCall,
	FunctionReentry = types.FunctionReentry,
	FunctionDefinition = types.FunctionDefinition,
	FunctionDefinitionNative = types.FunctionDefinitionNative,
	AnonymousFunction = types.AnonymousFunction,
	LiteralValue = types.LiteralValue,
	VariableReference = types.VariableReference,
	Tuple = types.Tuple;

var enable_parser_debug = false;
var parser_debug = function() {
	if(enable_parser_debug)
		console.error.apply(console, arguments);
}
global._lithp.set_parser_debug = function(val) { enable_parser_debug = val; };

var arityBuiltins = {
	print: '*',
	and: '*',
	or: '*',
	'+': '*',
	'++': '*',
	'-': '*',
	'/': '*',
	'*': '*',
	'+': '*',
	'+': '*',
	'+': '*',
	list: '*',
	flatten: '*',
	call: '*',
	'to-string': '*',
	'export': '*',
	'export-global': '*',
	invoke: '*',
	dict: '*',
};

var timespentParsing = 0;
global._lithp.getParserTime = function() { return timespentParsing; };

var EX_LITERAL = 1 << 0,             // Literal (1, 2, "test")
    EX_OPCHAIN = 1 << 1,             // opening OpChain '('
    EX_FUNCTIONCALL = 1 << 2,        // opening FunctionCall '('
    EX_NUMBER  = 1 << 3,             // Collect number (whole or float: [0-9.]+f?$)
    EX_ATOM    = 1 << 4,             // Collect atom
    EX_VARIABLE= 1 << 5,             // Variables
    EX_STRING_CHARACTER  = 1 << 6,   // Collect character
    EX_STRING_SINGLE = 1 << 7,       // Expecting a single quote to end '
    EX_STRING_DOUBLE = 1 << 8,       // Expecting a double quote to end "
    EX_PARAM_SEPARATOR   = 1 << 9,   // Expecting a space
    EX_CALL_END          = 1 << 10,  // Expected a ), end of call
    EX_OPCHAIN_END       = 1 << 11,  // Expect a ), end of opchain
    EX_COMMENT           = 1 << 12,  // Comments
    EX_COMPILED          = 1 << 13,  // Already compiled
    EX_FUNCTION_MARKER   = 1 << 14,  // #     next: Arg1,Arg2 :: (...)
    EX_FUNCTION_PARAM    = 1 << 15,  // #     this: Arg1
    EX_FUNCTION_PARAM_SEP= 1 << 16,  // #Arg1 this: ,
    EX_FUNCTION_BODY     = 1 << 17;  // #Arg1,Arg2  this: ::

var EX_TABLE = {
	EX_LITERAL: EX_LITERAL,
	EX_OPCHAIN: EX_OPCHAIN,
	EX_FUNCTIONCALL: EX_FUNCTIONCALL,
	EX_NUMBER: EX_NUMBER,
	EX_ATOM: EX_ATOM,
	EX_VARIABLE: EX_VARIABLE,
	EX_STRING_CHARACTER: EX_STRING_CHARACTER,
	EX_STRING_SINGLE: EX_STRING_SINGLE,
	EX_STRING_DOUBLE: EX_STRING_DOUBLE,
	EX_PARAM_SEPARATOR: EX_PARAM_SEPARATOR,
	EX_CALL_END: EX_CALL_END,
	EX_OPCHAIN_END: EX_OPCHAIN_END,
	EX_COMMENT: EX_COMMENT,
	EX_COMPILED: EX_COMPILED,
	EX_FUNCTION_MARKER: EX_FUNCTION_MARKER,
	EX_FUNCTION_PARAM: EX_FUNCTION_PARAM,
	EX_FUNCTION_PARAM_SEP: EX_FUNCTION_PARAM_SEP,
	EX_FUNCTION_BODY: EX_FUNCTION_BODY
};

function GET_EX (n) {
	var parts = [];
	for(var k in EX_TABLE)
		if(EX_TABLE[k] & n)
			parts.push(k);
	if(parts.length > 0)
		return parts.join(' | ');
	throw new Error("Expected value not known: " + n);
}

function ParserState (parent) {
	this.ops = [[]];
	this.ops_it = this.ops.iterator();
	this.current_word = '';
	this.expect = EX_OPCHAIN;
	this.depth = 0;
	this.in_variable = false;
	this.in_atom = false;
	this.quote_type = undefined;
	this.line = 1;
	this.character = 1;
	this.lines = [];
}

// Classify the given character(s). It could suit a number of different
// attributes at once.
ParserState.prototype.classify = function(ch) {
	var val = 0;
	if(typeof ch != 'string')
		return EX_COMPILED;
	if(ch.charCodeAt(0) == 9)
		return EX_PARAM_SEPARATOR;
	switch(ch) {
		case '(': val = EX_OPCHAIN | EX_FUNCTIONCALL; break;
		case ')': val = EX_CALL_END | EX_OPCHAIN_END; break;
		case ' ': case "\t": case "\r": case "\n":
			val = EX_PARAM_SEPARATOR; break;
		case "'": val = EX_STRING_SINGLE; break;
		case '"': val = EX_STRING_DOUBLE; break;
		case '%': val = EX_COMMENT; break;
		case '#': val = EX_FUNCTION_MARKER; break;
		case ',': val = EX_FUNCTION_PARAM_SEP; break;
		case ':': val = EX_FUNCTION_BODY; break; // Repeated twice for functions
		default:
			if(ch.match(/^[a-z][a-zA-Z0-9_]*$/))
				val = EX_ATOM;
			else if(ch.match(/^[A-Z][A-Za-z0-9_]*$/))
				val = EX_VARIABLE | EX_FUNCTION_PARAM;
			else if(ch.match(/^-?[0-9e][0-9e.]*$/))
				val = EX_NUMBER | EX_ATOM;
			else if(ch.length > 1 && ch.match(/^".*"$/))
				val = EX_STRING_DOUBLE;
			else if(ch.length > 1 && ch.match(/^'.*'$/))
				val = EX_STRING_SINGLE;
			else {
				//parser_debug("WARNING: assuming atom for: " + ch);
				val = EX_ATOM;
			}
	}
	// EX_STRING_CHARACTER is implied
	val |= EX_STRING_CHARACTER;
	return val;
};

ParserState.prototype.mapParam = function(P, chain, fnName) {
	var result = this.mapParamInner(P, chain, fnName);
	parser_debug("mapParam(", P, ") :: ", result);
	return result;
};

// Runs a series of replace actions over a string to replace escape sequences.
function parseString (str) {
	return str.replace(/\\(.)/g, function(FullMatch, Escape)  {
		switch(Escape) {
			case 'n': return "\n";
			case 'r': return "\r";
			case 't': return "\t";
			case '\\': return "\\";
			default: throw new Error('Unknown escape sequence: ' + Escape);
		}
	});
}

ParserState.prototype.mapParamInner = function(P, chain, fnName) {
	if(!Array.isArray(P)) {
		var cls = this.classify(P);
		parser_debug("Classified: " + GET_EX(cls));
		if(cls & EX_STRING_DOUBLE || cls & EX_STRING_SINGLE) {
			var parsed = parseString(P.slice(1, P.length - 1)); 
			if(cls & EX_STRING_DOUBLE)
				return new LiteralValue(parsed);
			else if(cls & EX_STRING_SINGLE)
				return Atom(parsed);
		} else if(cls & EX_VARIABLE) {
			if(fnName == 'get' || fnName == 'set' || fnName == 'var')
				return new VariableReference(P);
			return new FunctionCall("get/1", [new VariableReference(P)]);
		} else if(cls & EX_NUMBER)
			return new LiteralValue(Number(P));
		else if(cls & EX_ATOM)
			return Atom(P);
	} else {
		return this.convert(chain, P);
	}
	throw new Error("Unable to map parameter: " + inspect(P));
};

ParserState.prototype.convert = function(chain, curr) {
	var eleFirst = curr[0];
	var clsFirst = this.classify(eleFirst);
	var op;
	parser_debug("  First element: ", eleFirst);
	parser_debug("     Classified: ", GET_EX(clsFirst));
	if(curr.length == 0)
		return undefined;
	if(curr._fndef) {
		parser_debug("FNDEF");
		parser_debug("Params: ", curr._fnparams);
		var params = curr._fnparams;
		curr._fndef = false;
		//var newChain = new OpChain(chain);
		var body = this.convert(chain, curr);
		var anon = AnonymousFunction(chain, params, body);
		parser_debug("Got body for function:", body.toString());
		return anon;
	}
	if(clsFirst & EX_STRING_SINGLE) {
		// Convert to a (call (get 'FnName') Params...)
		parser_debug("STRING_SINGLE, convert to FunctionCall: (call/* (get/1 : " + eleFirst + " ... ");
		eleFirst = eleFirst.slice(1, eleFirst.length - 1);
		clsFirst = this.classify(eleFirst);
		parser_debug("    First element: ", eleFirst);
		parser_debug("    Re-Classified: ", GET_EX(clsFirst));
	}
	if(clsFirst & EX_ATOM) {
		// FunctionCall
		parser_debug(" PARSE TO FUNCTIONCALL: ", curr);
		var params = curr.slice(1);
		params = params.map(P => this.mapParam(P, chain, eleFirst));
		if(params.length == 0 && this.classify(eleFirst) & EX_NUMBER) {
			parser_debug("CONVERT TO LITERAL");
			return this.mapParam(eleFirst, chain, eleFirst);
		} else {
			var plen = params.length;
			if(eleFirst in arityBuiltins)
				plen = arityBuiltins[eleFirst];
			parser_debug("FUNCTIONCALL " + eleFirst + "/" + plen);
			op = new FunctionCall(eleFirst + "/" + plen, params);
			return op;
		}
	} else if(Array.isArray(eleFirst)) {
		// Must be an OpChain
		var newChain = new OpChain(chain);
		for(var i = 0; i < curr.length; i++) {
			parser_debug("Member " + i + " of chain: ", curr[i]);
			newChain.push(this.convert(newChain, curr[i]));
		}
		return newChain;
	} else if(curr.length > 0) {
		// Must be an OpChain
		parser_debug(" PARSE TO OPCHAIN");
		var newChain = new OpChain(chain);
		for(var i = 0; i < curr.length; i++) {
			parser_debug("Member " + i + " of chain: ", curr[i]);
			//process.exit();
			//chain.push(this.convert(newChain, curr[i]));
			newChain.push(this.mapParam(curr[i], newChain, eleFirst));
		}
		return newChain;
	} else {
		throw new Error("Unable to convert: " + inspect(curr));
	}
};

ParserState.prototype.finalize = function() {
	parser_debug("Finalize tree: ", this.ops);
	var chain = new OpChain();
	var it = this.ops.iterator();
	var curr;
	while((curr = it.next())) {
		var c = this.convert(chain, curr);
		parser_debug("Got from convert: ", c);
		if(c)
			chain.push(c);
	}
	return chain;
};

ParserState.prototype.parseBody = function(it, dest) {
	var params = this.current_word.length > 0 ?
		this.current_word.split(',') : [];
	parser_debug(" Body: params count: " + params.length);
	this.current_word = '';
	var d = [];
	d._fndef = true;
	d._fnparams = params;
	var chain = this.parseSection(it, d);
	parser_debug(" Body chain: " + inspect(chain, {depth: null, colors:true}));
	return chain;
};

var characters = 0;
ParserState.prototype.parseSection = function(it, dest) {
	var ch;
	var self = this;

	// Move to the next valid character.
	// Skips newlines, tabs, and also strips comment lines.
	function moveNext () {
		var expect = self.expect;
		var ch = it.next();
		if(ch === undefined)
			return ch;
		function ignore_line () {
			var chCode = ch.charCodeAt(0);
			while(chCode != 10) {
				ch = it.next();
				characters++;
				if(ch === undefined)
					return ch;
				chCode = ch.charCodeAt(0);
				if(chCode == 10) {
					self.character = 1;
					self.line++;
				}
			}
			ch = it.next();
			self.line++;
		}
		if(self.character == 1 && ch == '#') {
			ch = it.next();
			if(ch == '!') {
				ch = it.next();
				// Shebang, ignore line
				ignore_line();
			} else
				it.prev();
		}
		characters++;
		self.character++;
		if(ch === undefined)
			return ch;
		if(ch == '%' && !(self.expect & EX_STRING_CHARACTER)) {
			// Comment and not in speech, ignore this line.
			// Must keep running in a loop, in case there are more
			// comments.
			while(ch == '%') {
				parser_debug("COMMENT");
				ignore_line();
			}
		}
		return ch;
	}

	var depth = 1;

	while( (ch = moveNext()) != undefined) {
		parser_debug("Parse character: " + ch + " " + ch.charCodeAt(0).toString(10));

		// Classify the current character
		var cls = this.classify(ch);
		parser_debug("      Type     : " + GET_EX(cls));
		parser_debug("  expect_current: 0x" + this.expect.toString(16) + " (" + GET_EX(this.expect) + ")");
		parser_debug("     In var    : " + this.in_variable);
		if(this.quote_type !== undefined)
			parser_debug("     Quote Type: " + this.quote_type);

		// Skip spaces we are not expecting. This really only affects extra
		// space characters within a line.
		var expect = this.expect;
		if(cls & EX_PARAM_SEPARATOR &&
			!(expect & EX_PARAM_SEPARATOR) &&
			!(expect & EX_STRING_CHARACTER)) {
			parser_debug("Space when not expecting, ignoring");
			continue;
		}

		if(cls & EX_FUNCTION_BODY &&
		   !(expect & EX_FUNCTION_BODY) &&
		   !(expect & EX_STRING_CHARACTER)) {
			parser_debug("Found the extra :, ignoring");
			continue;
		}

		// When a variable goes from CAPStosmall
		if(cls & EX_ATOM &&
			(expect & EX_VARIABLE || expect & EX_FUNCTION_PARAM) &&
			this.in_variable) {
			parser_debug("Found atom but was expecting variable, supposing it is part of the name");
			this.current_word += ch;
			continue;
		}

		// When an atom goes from smallToCaps
		if(cls & EX_VARIABLE && expect & EX_ATOM && this.in_atom) {
			parser_debug("Found variable but was expecting atom, supposing it is part of the name");
			this.current_word += ch;
			continue;
		}

		// OpChain begin but expecting separator?
		if(cls & EX_OPCHAIN && expect & EX_PARAM_SEPARATOR) {
			// Change character to separator, next loop we will get the EX_OPCHAIN again.
			ch = ' ';
			cls = this.classify(ch);
			it.prev();
		}

		// Has the character been classified as something we are expecting?
		if(!(cls & expect)) {
			console.log("Error on line " + self.line + " at character " + self.character);
			console.log("  " + self.lines[self.line - 1]);
			console.log("  " + (" ".repeat(self.character + 1)) + "^");
			throw new Error("Unexpected character at " + self.line + ":" + self.character + " '" + ch + "' not expected (" + GET_EX(cls) + "), was expecting: " + GET_EX(this.expect));
		}

		if(cls & EX_OPCHAIN && !(expect & EX_STRING_CHARACTER)) {
			// Open an Opchain
			this.expect = EX_OPCHAIN | EX_NUMBER | EX_LITERAL | EX_STRING_DOUBLE | EX_STRING_SINGLE | EX_ATOM | EX_FUNCTION_MARKER | EX_VARIABLE;
			this.current_word = '';
			//dest.push([]);
			dest.push(this.parseSection(it, []));
		} else if(cls & EX_OPCHAIN_END && !(expect & EX_STRING_CHARACTER)) {
			// Close an OpChain
			if(this.current_word.length > 0)
				dest.push(this.current_word);
			this.expect = EX_OPCHAIN | EX_OPCHAIN_END | EX_FUNCTION_MARKER | EX_NUMBER | EX_STRING_SINGLE | EX_STRING_DOUBLE | EX_VARIABLE | EX_ATOM;
			this.current_word = '';
			this.in_variable = false;
			return dest;
		} else if(cls & EX_ATOM && expect & EX_ATOM) {
			// Continue an atom
			this.current_word += ch;
			this.in_atom = true;
			this.expect = EX_ATOM | EX_PARAM_SEPARATOR | EX_FUNCTION_MARKER | EX_OPCHAIN_END | EX_FUNCTIONCALL;
		} else if(cls & EX_PARAM_SEPARATOR && expect & EX_PARAM_SEPARATOR &&
		        !(expect & EX_STRING_CHARACTER) &&
		        !(expect & EX_FUNCTION_PARAM)) {
			// Space not in string, param separator
			parser_debug("SEPARATOR");
			if(this.current_word.length > 0) {
				dest.push(this.current_word);
			}
			this.current_word = '';
			this.expect = EX_OPCHAIN | EX_VARIABLE | EX_NUMBER | EX_LITERAL | EX_ATOM | EX_STRING_DOUBLE | EX_STRING_SINGLE | EX_ATOM | EX_FUNCTION_MARKER | EX_OPCHAIN_END;
			this.in_variable = false;
			this.in_atom = false;
		} else if(cls & EX_STRING_SINGLE && this.quote_type != '"') {
			// Start or end a single quote string, if not already in a double quote string
			if(!(expect & EX_STRING_CHARACTER)) {
				parser_debug("START SINGLE QUOTE STRING");
				this.expect = EX_STRING_CHARACTER | EX_STRING_SINGLE;
				this.current_word = ch;
				this.quote_type = "'";
			} else {
				parser_debug("END SINGLE QUOTE STRING");
				this.current_word += ch;
				if(this.current_word.length > 0)
					dest.push(this.current_word);
				this.expect = EX_PARAM_SEPARATOR | EX_OPCHAIN_END;
				this.current_word = '';
				this.quote_type = undefined;
			}
		} else if(cls & EX_STRING_DOUBLE && this.quote_type != "'") {
			// Start or end a double quote string, if not already in a single quote string
			if(!(expect & EX_STRING_CHARACTER)) {
				parser_debug("START DOUBLE QUOTE STRING");
				this.expect = EX_STRING_CHARACTER | EX_STRING_DOUBLE;
				this.current_word = ch;
				this.quote_type = '"';
			} else {
				parser_debug("END DOUBLE QUOTE STRING");
				this.current_word += ch;
				if(this.current_word.length > 0)
					dest.push(this.current_word);
				this.expect = EX_PARAM_SEPARATOR | EX_OPCHAIN_END;
				this.current_word = '';
				this.quote_type = undefined;
			}
		} else if(cls & EX_STRING_CHARACTER && expect & EX_STRING_CHARACTER) {
			// Continue string character reading
			this.current_word += ch;
		} else if(cls & EX_VARIABLE && expect & EX_VARIABLE) {
			// Start or continue variable
			this.in_variable = true;
			this.current_word += ch;
			this.expect = EX_VARIABLE | EX_PARAM_SEPARATOR | EX_OPCHAIN_END;
		} else if(cls & EX_NUMBER && expect & EX_NUMBER) {
			// Start or continue number
			this.current_word += ch;
			this.expect = EX_NUMBER | EX_PARAM_SEPARATOR | EX_OPCHAIN_END;
		} else if(cls & EX_FUNCTION_MARKER && expect & EX_FUNCTION_MARKER) {
			// Start or begin function
			parser_debug("BEGIN FUNCTION MARKER");
			// Current: #
			// Next: Arg1[,Arg2] :: Ops
			this.expect = EX_FUNCTION_PARAM | EX_FUNCTION_PARAM_SEP | EX_FUNCTION_BODY | EX_PARAM_SEPARATOR;
		} else if((cls & EX_FUNCTION_PARAM || cls & EX_FUNCTION_PARAM_SEP) &&
		           expect & EX_FUNCTION_PARAM) {
			// Continue reading function parameters
			this.current_word += ch;
			this.in_variable = true;
			parser_debug("CONTINUE FUNCTION PARAM: " + this.current_word);
		} else if(cls & EX_PARAM_SEPARATOR && expect & EX_FUNCTION_PARAM_SEP) {
			// Function parameters end, body starts soon
			parser_debug("PARAMS END");
			this.expect = EX_FUNCTION_BODY;
			this.in_variable = false;
		} else if(cls & EX_FUNCTION_BODY && expect & EX_FUNCTION_BODY) {
			parser_debug("FUNCTION BODY STARTS, current word: " + this.current_word);
			this.expect = EX_OPCHAIN;
			this.in_variable = false;
			dest.push(this.parseBody(it, []));
			this.current_word = '';
			return dest;
		} else {
			throw new Error('Unhandled combination');
		}

		parser_debug("State current: ");
		parser_debug("  Ops: ", this.ops);
		parser_debug("  Expect: " + GET_EX(this.expect));
		parser_debug("  Current word: " + this.current_word);
		parser_debug("  Depth: " + this.depth);
	}
	return dest;
}

ParserState.prototype.export = function() {
	var it = this.ops.iterator();
	return this.export_section(it);
};

ParserState.prototype.export_section = function(it) {
	var out = [];
	var curr;
	while((curr = it.next())) {
		if(curr._fndef) {
			curr = {code: this.export_section(curr.iterator()), _fndef: true, _fnparams: curr._fnparams}
			delete curr.code._fndef;
			delete curr.code._fnparams;
			out.push(curr);
		} else if(Array.isArray(curr)) {
			out.push(this.export_section(curr.iterator()));
		} else {
			out.push(curr);
		}
	}
	return out;
};

ParserState.prototype.unexport = function(ast) {
	if(ast && ast['code']) {
		var obj = this.unexport(ast['code']);
		obj._fndef = ast['_fndef'];
		obj._fnparams = ast['_fnparams'];
		return obj;
	} else if(Array.isArray(ast)) {
		return ast.map(E => this.unexport(E));
	}
	return ast;
}

function BootstrapParser (code, opts) {
	opts = (typeof opts == 'object') ? opts : {};
	opts['finalize'] = (opts['finalize'] !== undefined) ? opts['finalize'] : true;
	opts['ast']      = (opts['ast'] !== undefined) ? opts['ast'] : false;

	characters = 0;
	var start = (new Date()).getTime();
	var state = new ParserState();
	if(opts['ast']) {
		var parsed = code;
		if(typeof code == 'string')
			parsed = JSON.parse(code);
		state.ops = [state.unexport(parsed)];
	} else {
		var it = code.split('').iterator();
		state.lines = code.split(/\n\r?/);
		state.ops = state.parseSection(it, []);
	}
	if(opts['finalize']) {
		var fin = state.finalize();
		timespentParsing += (new Date()).getTime() - start;
		return fin;
	} else {
		return state;
	}
}

exports.BootstrapParser = BootstrapParser;


}).call(this,typeof global !== "undefined" ? global : typeof self !== "undefined" ? self : typeof window !== "undefined" ? window : {})
},{"./../../index":10,"util":137}],58:[function(require,module,exports){
/**
 * Parser V1, Platform V0, switch() implementation.
 *
 * Provides:
 *  - switch/*
 *  - case/2
 *  - default/1
 *
 * This is implemented in hand-compiled Lithp, and tries to use as little
 * FunctionDefinitionNative calls as possible. The more that can be
 * implemented in the language itself, the better.
 */


var util = require('util'),
	inspect = util.inspect;
var lithp = require('./../../.'),
	Lithp = lithp.Lithp,
	debug = Lithp.debug,
	types = lithp.Types,
	OpChain = types.OpChain,
	Atom = types.Atom,
	FunctionCall = types.FunctionCall,
	FunctionReentry = types.FunctionReentry,
	FunctionDefinition = types.FunctionDefinition,
	FunctionDefinitionNative = types.FunctionDefinitionNative,
	AnonymousFunction = types.AnonymousFunction,
	LiteralValue = types.LiteralValue,
	VariableReference = types.VariableReference,
	Tuple = types.Tuple;

function lib_case (lithp) {
	/**
	 (
		% For use with switch/*, a case statement that returns a function that
		% is called by switch/*, and if the Value given by switch/* matches,
		% {ok, Result} is returned. Otherwise {false} is returned.
		(def case #Eq,Result :: (
			% Ignore:
			% // Return a function that retains access to the outside closure
			% // variables (Eq and Result) to perform a comparison.
			% // This is a little convoluted because we need to ensure a new
			% // closure is generated that has access to the Eq and Result values.
			%
			% //If we did not do this, we may end up using old values of Eq and Result.
			%
			% TODO: Verify the above logic is correct. Since each call is already in
			%       a new OpChain, it should retain access to the variables.
			(scope #Value :: (
				(if (== Eq Value) ((tuple ok Result))
					(else (tuple false))
				)
			))
		))
	 )
	*/
}

function lib_default (lithp) {
	/**
		% For use with switch/*, a default value if no matching cases are found.
		(def default #Result :: (tuple default Result))
	**/
	var default1 = new OpChain();

	var default1_body = new OpChain(default1,
		new FunctionCall("tuple/*", [
			Atom("default"),
			new FunctionCall("get/1", [new VariableReference("Result")])
		])
	);
	
	/**
	 * (print (default "Foo"))
	 */
	var chain = new OpChain();
	chain.push(
		new FunctionCall("def/2", [
			Atom("default"),
			AnonymousFunction(default1, ['Result'], default1_body)
		])
	);
	chain.push(
		new FunctionCall("print/*", [
			new FunctionCall("default/1", [new LiteralValue("Foo")])
		])
	);
	/**
	 * (print (inspect (default "Foo") true true))
	 */
	chain.push(
		new FunctionCall("print/*", [
			new FunctionCall("inspect/3", [
				new FunctionCall("default/1", [new LiteralValue("Foo")]),
				Atom('true'),
				Atom('true')
			])
		])
	);
	/**
	 * (assert (== (default "Foo") (tuple default "Foo")))
	 */
	chain.push(
		new FunctionCall("assert/1", [
			new FunctionCall("equal/2", [
				new FunctionCall("default/1", [new LiteralValue("Foo")]),
				new FunctionCall("tuple/*", [
					Atom("default"),
					new LiteralValue("Foo")
				])
			])
		])
	);

	chain.importClosure(lithp.functions);
	lithp.run(chain);
}

function lib_switch_inner (chain) {
	/*
		(def _switch_inner #Possibility :: (
			% Use call/* to call the provided function with one parameter.
		// Value comes from chain
			(var Result (call Possibility Value))
			(if (== (tuple-get Result 0) ok) (Result)
				(else (
					(if (== (tuple-get Result 0) default) (
							(set Default (tuple-get Result 1))
						) (else ((tuple false)))
					)
				))
			)
		))
	 */
}

function lib_switch_loop (chain) {
	/**
		(def _switch_loop #List :: (
			(if (== 0 (length List)) (
				(tuple notfound)
			) (else (
				(var Head (head List))
				(var Tail (tail Possibiilties))
				(var Test (call _switch_inner Head))
				(if (== (tuple-get Test 0) ok) (Test)
					(else (
						% Must be tuple false
						% Could skip this check
						(assert (== (tuple-get Test 0) false))
						% Call recursively to check the rest
						(call _switch_loop Tail)
					))
				)
			)))
		))
	*/
}

function lib_switch (lithp) {
	/**
		(def switch/* #Params :: (
			(var Value (head Params))
			(var Possibilities (tail Params))
			% Scope of _switch_inner is this function call
			(var Default nil)
			% Test if the given possibility matches. Also detects the presence
			% of a default clause, and sets Default if found.
(def _switch_inner #Possibility ... from lib_switch_inner.
			% Recursive local function that runs through the list of possibilities,
			% returning {ok, Result} if a match is found, or {notfound}.
(def _switch_loop #List ... from lib_switch_loop
			(var Test (_switch_loop Possibilities))
			(if (== (tuple-get Test 0) notfound) (
				% Not found return Default or nil
				(if (!= Default nil) (Default)
					% Return nil if there is no default tuple found
				    (else (nil))
				)
			) else (
				% Could skip this check
				(assert (== (tuple-get Test 0) ok))
				(tuple-get Test 1)
			))
		)
	*/
}

exports.test = (lithp) => {
	console.log("lib-parser-switch.js");
	lib_default(lithp);
};

exports.functions = {
	"case": lib_case,
	"default": lib_default,
	"switch": lib_switch
};

},{"./../../.":10,"util":137}],59:[function(require,module,exports){
/**
 * Standard library for Parser V1, Platform V0.
 *
 * Contains native and hand-compiled functions.
 * Incorporates additional library functions.
 */

"use strict";

var util = require('util'),
	inspect = util.inspect;
var lithp = require('./../../.'),
	Lithp = lithp.Lithp,
	debug = lithp.debug,
	types = lithp.Types,
	OpChain = types.OpChain,
	Atom = types.Atom,
	GetAtoms = types.GetAtoms,
	FunctionCall = types.FunctionCall,
	FunctionReentry = types.FunctionReentry,
	FunctionDefinition = types.FunctionDefinition,
	FunctionDefinitionNative = types.FunctionDefinitionNative,
	AnonymousFunction = types.AnonymousFunction,
	LiteralValue = types.LiteralValue,
	VariableReference = types.VariableReference,
	Tuple = types.Tuple;
var lib_parser_switch = require('./lib-parser-switch');

var atomTrue = Atom('true'),
    atomFalse = Atom('false');

var builtins = {};
function builtin (name, params, body) {
	builtins[name] = {params: params, body: body};
}

function builtin_def () {
}

exports.test = (lithp) => {
	lib_parser_switch.test(lithp);
};

exports.setup = function(lithp) {
	var count = 0;
	for(var k in builtins) {
		lithp.builtin(k, builtins[k].params, builtins[k].body);
		count++;
	}
	// TODO: import functions from lib_parser_switch
	return count;
};

// Used to instantiate classes when the number of parameters it not
// known. Uses apply to instantiate (which is a little trickier than
// usual.)
function newClass (Cls) {
	// Function.bind.apply's first argument is ignored. Thus, it doesn't
	// matter that it's included in arguments.
	return new (Function.bind.apply(Cls, arguments));
}

function error (message) { throw new Error(message); };

/**
 * Implement all of the native types used by the interpreter so that a
 * parser written in Lithp can construct a parsing tree for the interpreter.
 */

// Perform an Object comparison
builtin("equal", ['A', 'B'], (A, B) =>
	Object.equals(A, B) ? atomTrue : atomFalse
);

builtin("get-opchain-closure-current", [], State => new LiteralValue(State.closure));

builtin("opchain-closure", ['Owner', 'Parent'], (Owner, Parent) =>
	new LiteralValue(new OpChainClosure(Owner, Parent))
);

builtin("opchain-closure-any-defined", ['Opchain', 'Name'], (Opchain, Name) =>
	new LiteralValue(Opchain.any_defined(Name))
);

builtin("opchain-closure-set", ['Opchain', 'Name', 'Value'], (Opchain, Name, Value) => {
	Opchain.set(Name, Value);
	return new LiteralValue(Opchain);
});

builtin("opchain-closure-set-immediate", ['Opchain', 'Name', 'Value'], (Opchain, Name, Value) => {
	Opchain.set_immediate(Name, Value);
	return new LiteralValue(Opchain);
});

builtin("opchain-closure-try-set", ['Opchain', 'Name', 'Value'], (Opchain, Name, Value) =>
	new LiteralValue(Opchain.try_set(Name, Value))
);

builtin("opchain-closure-get", ['Opchain', 'Name'], (Opchain, Name) =>
	new LiteralValue(Opchain.get(Name))
);


builtin("opchain", ['Parent', 'Ops'], (Parent, Ops) =>
	new LiteralValue(new OpChain(Parent, Ops))
);

builtin("opchain-push", ['Opchain', 'Value'], (Opchain, Value) => {
	Opchain.push(Value);
	return new LiteralValue(Opchain);
});

builtin("opchain-get", ['Opchain'], (Opchain) =>
	new LiteralValue(Opchain.get())
);

builtin("opchain-next", ['Opchain'], (Opchain) =>
	new LiteralValue(Opchain.next())
);

builtin("opchain-call-immediate", ['Opchain'], (Opchain) =>
	new LiteralValue(Opchain.call_immediate())
);

function alias (newname, oldname) {
	return builtin(newname, [], function() { return builtins[oldname].apply(this, arguments); });
}

builtin("literal-value", ["Value"], Value => new LiteralValue(Value));
alias('lit', 'literal-value');

builtin("function-call", ['Name', 'Params'], (Name, Params) =>
	new LiteralValue(new FunctionCall(Name, Params))
);

builtin("function-definition", ['Parent', 'Name', 'Params', 'Body'], (Parent, Name, Params, Body) =>
	new LiteralValue(new FunctionDefinition(Parent, Name, Params, Body))
);

builtin("lambda", ['Parent', 'Params', 'Body'], (Parent, Params, Body) =>
	new LiteralValue(new AnonymousFunction(Parent, Params, Body))
);

builtin("function-definition-native", ['Name', 'Params', 'Body'], (Name, Params, Body) =>
	new LiteralValue(new FunctionDefinitionNative(Name, Params, Body))
);

builtin("recurse/*", [], function(Arguments, State) {
	// Call the current function again with the given arguments.
	// We do this by calling call/* with the current State.
	// TODO: should just reset the current opchain, and set parameters
	//       to Arguments. Allows for infinite recursion.
	var args = [State.call(), Arguments, State];
	return builtins["call/*"].apply(this, args);
});

// TODO: Test:
// (def catch #Callback :: ((#Exception :: ((call Callback Exception))))
builtin_def('catch_native', (chain) => {
	var fn_body = new OpChain(chain,
		new FunctionCall('call/2', [
			new FunctionCall('get/1', [new VariableReference('Callback')]),
			new FunctionCall('get/1', [new VariableReference('Exception')])
		])
	);
	return new OpChain(chain, new AnonymousFunction(chain, ['Exception'], fn_body));
});

builtin('atoms', [], () => GetAtoms.map(A => A.name));

function atomBool (A) {
	return A == atomTrue ? true : false;
}

builtin('inspect/2', ['Object', 'Deep'], (O, Deep) => inspect(O, {depth: atomBool(Deep) ? null : undefined}));
builtin('inspect/3', ['Object', 'Deep', 'Color'], (O, Deep, Color) => inspect(O, {depth: atomBool(Deep) ? null : undefined, colors: atomBool(Color)}));

function lib_each (chain) {
	/**
	 (
	 	// TODO: keep track of count, also pass it to callback
	 	(def each #List,Callback :: (
			((if (== (length List) 0) (done)
			     (else (
				 	(var Head (head List))
					(var Tail (tail List))
					(call Callback List)
					(each Tail Tail)
				 ))
			))
		)
	 )
	 */
}

function lib_with (chain) {
	/**
	 (
	 	(def with #Value,Callback :: (
			(call Callback Value)
		))
	 )
	 */
}

},{"./../../.":10,"./lib-parser-switch":58,"util":137}],60:[function(require,module,exports){
module.exports = "#!./run.js\n% Entry point for the Lithp REPL.\n%\n% vim: set syntax=lithp noet ts=4:\n% See syntax file in node_modules/lithp/syntax/vim/lithp.vim\n(\n\t(import \"modules/repl\")\n\n\t(print \"Welcome to Lithp v\" (host-version) \"running on\" (host))\n\t(print \"Type \\\\q exit. Type ? for help.\")\n\n\t(if (== (host) \"Node.js\") (\n\t\t(repl-loop)\n\t) (else (\n\t\t(import html-toolkit)\n\t\t(htmlOnLoad # :: ((repl-loop)))\n\t)))\n)\n";

},{}],61:[function(require,module,exports){
module.exports=[[["import","\"lists\""],["def","f",{"code":[[["/",["*","A","B","C"],["+","B","C",["-","0","A"]],["+","A","C",["-","0","B"]],["+","A","B",["-","0","C"]]]]],"_fndef":true,"_fnparams":["A","B","C"]}],["print",["f","1","1","1"]],["print",["f","3","4","5"]],["print",["f","42","42","3.14"]],["print",["f","14","6","12"]],["print",["f","6","12","14"]],["print",["f","0.5","0.6","0.7"]]]]
},{}],62:[function(require,module,exports){
module.exports = "% A simple algorithm to output the aspest ratio of a circle.\n(\n\t(import \"lists\")\n\t(def f #A,B,C::(\n\t\t(/ (* A B C)\n\t\t   (+ B C (- 0 A))\n\t\t   (+ A C (- 0 B))\n\t\t   (+ A B (- 0 C))\n\t\t)\n\t))\n\t(print (f 1   1   1))    % Output: 1\n\t(print (f 3   4   5))    % Output: 1.25\n\t(print (f 42  42  3.14)) % Output: 6.9476062266936145\n\t(print (f 14  6   12))   % Output: 1.575\n\t(print (f 6   12  14))   % Output: 1.575\n\t(print (f 0.5 0.6 0.7))  % Output: 1.09375\n)\n";

},{}],63:[function(require,module,exports){
module.exports=[[["def","get-fn-by-name",{"code":[[["var","R1",["+","Name","\"/\""]],["var","Ref",["+","R1","Arity"]],["get",["to-string","Ref"]]]],"_fndef":true,"_fnparams":["Name","Arity"]}],["'print'","\"+ is\"",["get-fn-by-name","+","*"]],["call",["get-fn-by-name","\"print\"","*"],"\"Testing\""]]]
},{}],64:[function(require,module,exports){
module.exports = "% Test calling functions using quoted atoms, and also\n% grabbing a currently defined function for use with\n% call/*.\n(\n\t(def get-fn-by-name #Name,Arity :: (\n\t\t% BUGGED, parsed incorrectly: (var Ref (+ (Name (+ \"/\" Arity))))\n\t\t%         Seems to get an OpChain instead of the result of (+ \"/\" Arity)\n\t\t(var R1 (+ Name \"/\"))\n\t\t(var Ref (+ R1 Arity))\n\t\t(get (to-string Ref))\n\t))\n\t('print' \"+ is\" (get-fn-by-name + *))\n\t(call (get-fn-by-name \"print\" *) \"Testing\")\n)";

},{}],65:[function(require,module,exports){
module.exports=[[["import","\"bignum\""],["import","\"lists\""],["var","FL",["dict"]],["var","Base","16"],["def","b",{"code":[[["bignum","N"]]],"_fndef":true,"_fnparams":["N"]}],["def","s",{"code":[[["to-string","N","Base"]]],"_fndef":true,"_fnparams":["N"]}],["def","fib",{"code":[[["if",["b<=","N",["b","2"]],[["b","1"]],[["+",["fibFL",["b-","N",["b","2"]]],["fibFL",["b-","N",["b","1"]]]]]]]],"_fndef":true,"_fnparams":["N"]}],["def","fibFL",{"code":[[["if",["dict-present","FL",["s","N"]],[["dict-get","FL",["s","N"]]],[["var","I",["fib","N"]],["set","FL",["dict-set","FL",["s","N"],"I"]],["I"]]]]],"_fndef":true,"_fnparams":["N"]}],["def","fib-orial",{"code":[[["bprod",["map",["seq","1","N"],["scope",{"code":[[["fib",["b","I"]]]],"_fndef":true,"_fnparams":["I"]}]]]]],"_fndef":true,"_fnparams":["N"]}],["each",["seq","2","20"],["scope",{"code":[[["print",["s",["fib-orial","N"]]]]],"_fndef":true,"_fnparams":["N"]}]]]]
},{}],66:[function(require,module,exports){
module.exports = "% Bignum version of fib-orial test.\n% Only works under Node.js with the \"bignum\" NPM package installed.\n% Will not work in Web IDE.\n(\n\t(import \"bignum\")\n\t(import \"lists\")\n\t(var FL (dict))\n\t(var Base 16)\n\t(def b #N::((bignum N)))\n\t(def s #N::((to-string N Base)))\n\t(def fib #N::(\n\t\t(if (b<= N (b 2)) (\n\t\t\t(b 1)\n\t\t) (\n\t\t\t(+ (fibFL (b- N (b 2))) (fibFL (b- N (b 1))))\n\t\t))\n\t))\n\t(def fibFL #N::((if (dict-present FL (s N)) ((dict-get FL (s N))) ((var I (fib N))(set FL (dict-set FL (s N) I))(I)))))\n\t(def fib-orial #N::((bprod (map (seq 1 N) (scope #I::((fib (b I))))))))\n\t(each (seq 2 20) (scope #N :: ((print (s (fib-orial N))))))\n\t%(print (fib-orial (b 5)))\n)\n";

},{}],67:[function(require,module,exports){
module.exports=[[["import","lists"],["import","math"],["import","readline"],["import","switch"],["import","stderr"],["var","Acc","0"],["def","=",{"code":[["Value"]],"_fndef":true,"_fnparams":["Ignored","Value"]}],["def","v",{"code":[["Acc"]],"_fndef":true,"_fnparams":[]}],["def","p",{"code":[[["print",["format-acc"]],["v"]]],"_fndef":true,"_fnparams":[]}],["def","f",{"code":[[["floor","Acc"]]],"_fndef":true,"_fnparams":[]}],["def","c",{"code":[[["ceil","Acc"]]],"_fndef":true,"_fnparams":[]}],["def","e",{"code":[[["exit"]]],"_fndef":true,"_fnparams":[]}],["def","acc-op",["scope",{"code":[[["var","Code",["+","\"(\"","Op","\" Acc \"","Value","\")\""]],["stderr-write",["+","\"Code: \"","Code","\"\\n\""]],["eval","Code"]]],"_fndef":true,"_fnparams":["Op","Value"]}]],["var","Commands",["dict",["tuple","\"c\"","\"Ceil of Acc\""],["tuple","\"f\"","\"Floor of Acc\""],["tuple","\"h\"","\"Display this help\""],["tuple","\"?\"","\"Display this help\""],["tuple","\"e\"","\"Exit\""],["tuple","\"p\"","\"Print Acc\""],["tuple","\"v\"","\"Current value of Acc\""],["tuple","\"=\"","\"Set Acc to given value\""],["tuple","\"H\"","\"Set hex mode output\""],["tuple","\"D\"","\"Set decimal mode output\""],["tuple","\"B\"","\"Set binary mode output\""]]],["var","AccFormat","\"D\""],["def","format-acc",{"code":[[["format-acc","AccFormat"]]],"_fndef":true,"_fnparams":[]}],["var","FormatAccCaseHex",["case","\"H\"",["scope",{"code":[[["+","\"0x\"",["to-string","Acc","16"]]]],"_fndef":true,"_fnparams":[]}]]],["var","FormatAccCaseDecimal",["case","\"D\"",["scope",{"code":[[["get","Acc"]]],"_fndef":true,"_fnparams":[]}]]],["var","FormatAccCaseBinary",["case","\"B\"",["scope",{"code":[[["+","\"B\"",["to-string","Acc","2"]]]],"_fndef":true,"_fnparams":[]}]]],["var","FormatAccCaseList",["list","FormatAccCaseHex","FormatAccCaseDecimal","FormatAccCaseBinary"]],["def","format-acc",{"code":[[["switch","Format","FormatAccCaseList"]]],"_fndef":true,"_fnparams":["Format"]}],["def","set-acc-format",{"code":[[["set","AccFormat",["get","Format"]],["v"]]],"_fndef":true,"_fnparams":["Format"]}],["var","BuiltinsAvailable",["dict",["tuple","1",["list","abs","acos","acosh","asin","asinh","atan","atanh","cbrt","ceil","clz32","cos","cosh","floor","hypot","log","log10","log1p","log2","sign","sin","sinh","aqrt","tan","tanh"]],["tuple","2",["list","min","max","round","pow","imul","exp","expm1","fround","round"]]]],["def","show-help",{"code":[[["print","\"Available commands:\""],["each",["dict-keys","Commands"],{"code":[[["print","\"    \"","Command","\" -> \"",["index","Commands","Command"]]]],"_fndef":true,"_fnparams":["Command"]}],["print","\"Syntax: op value value value\""],["print","\"    eg: = 1\""],["print","\"      : + 2 2 3 v (sinh (pi))\""],["print","\"      : = 33.548739357257745\""],["print","\"Available builtins:\""],["print",["join",["map",["dict-keys",["dict-get","BuiltinsAvailable","1"]],{"code":[[["+","\"(\"",["dict-get",["dict-get","BuiltinsAvailable","1"],"Name"],"\" N)\""]]],"_fndef":true,"_fnparams":["Name"]}],"\", \""]],["print",["join",["map",["dict-keys",["dict-get","BuiltinsAvailable","2"]],{"code":[[["+","\"(\"",["dict-get",["dict-get","BuiltinsAvailable","2"],"Name"],"\" A B)\""]]],"_fndef":true,"_fnparams":["Name"]}],"\", \""]],["get","Acc"]]],"_fndef":true,"_fnparams":[]}],["var","CasePrint",["case","\"p\"",["scope",{"code":[[["p"]]],"_fndef":true,"_fnparams":[]}]]],["var","CaseQuit",["case","\"q\"",["scope",{"code":[[["e"]]],"_fndef":true,"_fnparams":[]}]]],["var","CaseCurrent",["case","\"v\"",["scope",{"code":[[["v"]]],"_fndef":true,"_fnparams":[]}]]],["var","CaseFloor",["case","\"f\"",["scope",{"code":[[["f"]]],"_fndef":true,"_fnparams":[]}]]],["var","CaseCeil",["case","\"c\"",["scope",{"code":[[["c"]]],"_fndef":true,"_fnparams":[]}]]],["var","CaseHex",["case","\"H\"",["scope",{"code":[[["set-acc-format","\"H\""]]],"_fndef":true,"_fnparams":[]}]]],["var","CaseDecimal",["case","\"D\"",["scope",{"code":[[["set-acc-format","\"D\""]]],"_fndef":true,"_fnparams":[]}]]],["var","CaseBinary",["case","\"B\"",["scope",{"code":[[["set-acc-format","\"B\""]]],"_fndef":true,"_fnparams":[]}]]],["var","CaseHelp1",["case","\"h\"",["scope",{"code":[[["show-help"]]],"_fndef":true,"_fnparams":[]}]]],["var","CaseHelp2",["case","\"?\"",["scope",{"code":[[["show-help"]]],"_fndef":true,"_fnparams":[]}]]],["var","CaseDefault",["default",["scope",{"code":[[["print","\"Unknown command\""],["get","Acc"]]],"_fndef":true,"_fnparams":["Given"]}]]],["var","CaseList",["list","CasePrint","CaseQuit","CaseCurrent","CaseFloor","CaseCeil","CaseHex","CaseDecimal","CaseBinary","CaseHelp1","CaseHelp2","CaseDefault"]],["def","parse",{"code":[[["var","Matches",["match","Entry","\"([-=+*/!@#$%^&<>a-z]+) (.*)$\""]],["if",["==",["null"],"Matches"],[["switch","Entry","CaseList"]],["else",[["var","Tail",["index","Matches","2"]],["set","Tail",["replace","Tail",["regex","\"(?:^|\\\\s)([a-z]+)(?=\\\\s|$)\"","\"g\""],["js-bridge",{"code":[[["+","\"(\"",["trim","Value"],"\") \""]]],"_fndef":true,"_fnparams":["Value"]}]]],["try",[["acc-op",["index","Matches","1"],"Tail"]],{"code":[[["stderr-write",["+","\"Failed to parse: \"",["to-string","E"],"\"\\n\""]],["c"]]],"_fndef":true,"_fnparams":["E"]}]]]]]],"_fndef":true,"_fnparams":["Entry"]}],["def","input-loop",{"code":[[["readline",["+",["format-acc"],"\">\""],["scope",{"code":[[["set","Acc",["parse","Value"]],["input-loop"]]],"_fndef":true,"_fnparams":["Value"]}]]]],"_fndef":true,"_fnparams":[]}],["if",["==",["host"],"\"Node.js\""],[["input-loop"]],["else",[["import","html-toolkit"],["htmlOnLoad",{"code":[[["input-loop"]]],"_fndef":true,"_fnparams":[]}]]]]]]
},{}],68:[function(require,module,exports){
module.exports = "% Simple Accumulative Calculator\n%\n% Works best in Node.js environment. Expect issues running in Web IDE.\n(\n\t(import lists)\n\t(import math)\n\t(import readline)\n\t(import switch)\n\n\t(import stderr)\n\n\t(var Acc 0)\n\n\t(def = #Ignored,Value :: (Value))\n\t(def v # :: (Acc))\n\t(def p # :: ((print (format-acc))(v)))\n\t(def f # :: ((floor Acc)))\n\t(def c # :: ((ceil Acc)))\n\t(def e # :: ((exit)))\n\t(def acc-op (scope #Op,Value :: (\n\t\t(var Code (+ \"(\" Op \" Acc \" Value \")\"))\n\t\t(stderr-write (+ \"Code: \" Code \"\\n\"))\n\t\t(eval Code)\n\t)))\n\n\t(var Commands (dict\n\t\t(tuple \"c\" \"Ceil of Acc\")\n\t\t(tuple \"f\" \"Floor of Acc\")\n\t\t(tuple \"h\" \"Display this help\")\n\t\t(tuple \"?\" \"Display this help\")\n\t\t(tuple \"e\" \"Exit\")\n\t\t(tuple \"p\" \"Print Acc\")\n\t\t(tuple \"v\" \"Current value of Acc\")\n\t\t(tuple \"=\" \"Set Acc to given value\")\n\t\t(tuple \"H\" \"Set hex mode output\")\n\t\t(tuple \"D\" \"Set decimal mode output\")\n\t\t(tuple \"B\" \"Set binary mode output\")\n\t))\n\n\t(var AccFormat \"D\")\n\t(def format-acc # :: ((format-acc AccFormat)))\n\t(var FormatAccCaseHex     (case \"H\" (scope # :: ((+ \"0x\" (to-string Acc 16))))))\n\t(var FormatAccCaseDecimal (case \"D\" (scope # :: ((get Acc)))))\n\t(var FormatAccCaseBinary  (case \"B\" (scope # :: ((+ \"B\" (to-string Acc 2))))))\n\t(var FormatAccCaseList (list FormatAccCaseHex FormatAccCaseDecimal FormatAccCaseBinary))\n\t(def format-acc #Format :: (\n\t\t(switch Format FormatAccCaseList)\n\t))\n\t(def set-acc-format #Format :: (\n\t\t(set AccFormat (get Format))\n\t\t(v)\n\t))\n\n\t(var BuiltinsAvailable (dict\n\t\t(tuple 1 (list abs acos acosh asin asinh atan atanh cbrt ceil clz32\n\t\t               cos cosh floor hypot log log10\n\t\t               log1p log2 sign sin sinh aqrt tan tanh))\n\t\t(tuple 2 (list min max round pow imul exp expm1 fround round))\n\t))\n\t(def show-help # :: (\n\t\t(print \"Available commands:\")\n\t\t(each (dict-keys Commands) #Command :: (\n\t\t\t(print \"    \" Command \" -> \" (index Commands Command))\n\t\t))\n\t\t(print \"Syntax: op value value value\")\n\t\t(print \"    eg: = 1\")\n\t\t(print \"      : + 2 2 3 v (sinh (pi))\")\n\t\t(print \"      : = 33.548739357257745\")\n\t\t(print \"Available builtins:\")\n\t\t(print (join (map (dict-keys (dict-get BuiltinsAvailable 1)) #Name :: (\n\t\t\t(+ \"(\" (dict-get (dict-get BuiltinsAvailable 1) Name) \" N)\"))) \", \"\n\t\t))\n\t\t(print (join (map (dict-keys (dict-get BuiltinsAvailable 2)) #Name :: (\n\t\t\t(+ \"(\" (dict-get (dict-get BuiltinsAvailable 2) Name) \" A B)\"))) \", \"\n\t\t))\n\t\t(get Acc)\n\t))\n\n\t(var CasePrint   (case \"p\" (scope # :: ((p)))))\n\t(var CaseQuit    (case \"q\" (scope # :: ((e)))))\n\t(var CaseCurrent (case \"v\" (scope # :: ((v)))))\n\t(var CaseFloor   (case \"f\" (scope # :: ((f)))))\n\t(var CaseCeil    (case \"c\" (scope # :: ((c)))))\n\t(var CaseHex     (case \"H\" (scope # :: ((set-acc-format \"H\")))))\n\t(var CaseDecimal (case \"D\" (scope # :: ((set-acc-format \"D\")))))\n\t(var CaseBinary  (case \"B\" (scope # :: ((set-acc-format \"B\")))))\n\t(var CaseHelp1   (case \"h\" (scope # :: ((show-help)))))\n\t(var CaseHelp2   (case \"?\" (scope # :: ((show-help)))))\n\t(var CaseDefault (default  (scope #Given :: ((print \"Unknown command\")(get Acc)))))\n\t(var CaseList    (list CasePrint CaseQuit    CaseCurrent CaseFloor CaseCeil\n\t                       CaseHex   CaseDecimal CaseBinary\n\t                       CaseHelp1 CaseHelp2   CaseDefault))\n\n\t(def parse #Entry :: (\n\t\t(var Matches (match Entry \"([-=+*/!@#$%^&<>a-z]+) (.*)$\"))\n\t\t(if (== (null) Matches) (\n\t\t\t(switch Entry CaseList)\n\t\t) (else (\n\t\t\t(var Tail (index Matches 2))\n\t\t\t(set Tail (replace Tail (regex \"(?:^|\\\\s)([a-z]+)(?=\\\\s|$)\" \"g\") (js-bridge #Value :: (\n\t\t\t\t(+ \"(\" (trim Value) \") \")\n\t\t\t))))\n\t\t\t(try (\n\t\t\t\t(acc-op (index Matches 1) Tail)\n\t\t\t) #E :: (\n\t\t\t\t(stderr-write (+ \"Failed to parse: \" (to-string E) \"\\n\"))\n\t\t\t\t(c)\n\t\t\t))\n\t\t)))\n\t))\n\n\t(def input-loop # :: (\n\t\t(readline (+ (format-acc) \">\") (scope #Value :: (\n\t\t\t(set Acc (parse Value))\n\t\t\t(input-loop)\n\t\t)))\n\t))\n\n\t(if (== (host) \"Node.js\") (\n\t\t(input-loop)\n\t) (else (\n\t\t(import html-toolkit)\n\t\t(htmlOnLoad # :: ((input-loop)))\n\t)))\n)\n";

},{}],69:[function(require,module,exports){
module.exports=[[["var","A","1"],["var","B",["+","A","1"]],["var","C",["+","B","1"]],["print","\"A:\"","A","\"B:\"","B","\"C:\"","C"],["if",["==","A",["-","C","2"]],[["print","\"Well now\""],["if",["==","B",["-","C","1"]],[["print","\"All is well\""]],["else",[["print","\"Oh\""]]]]],["else",[["print","\"Oh, ok\""]]]]]]
},{}],70:[function(require,module,exports){
module.exports = "% This is a test of nested if and print states to check control flow.\n% One of the original \"complex\" examples, though now is fairly straight forward.\n(\n\t(var A 1)\n\t(var B (+ A 1))\n\t(var C (+ B 1))\n\t(print \"A:\" A \"B:\" B \"C:\" C)\n\t(if (== A (- C 2)) (\n\t\t(print \"Well now\")\n\t\t(if (== B (- C 1)) (\n\t\t\t(print \"All is well\")\n\t\t) (else (\n\t\t\t(print \"Oh\")\n\t\t)))\n\t) (else (\n\t\t(print \"Oh, ok\")\n\t)))\n)\n";

},{}],71:[function(require,module,exports){
module.exports=[[["print","\"Definitions:\"",["definitions"]],["define","test","true"],["print","\"Definitions:\"",["definitions"]],["if",["defined","test"],[["print","\"'test' is defined\""]],["else",[["print","\"'test' is not defined!\""]]]],["print","\"Value of 'test':\"",["get-def","test"]],["if",["defined","'DEBUG'"],[["print","\"DEBUG mode is on\""]],["else",[["print","\"DEBUG mode is not on.\""]]]],["var","MySecretValue","\"A secret value\""],["var","Fn",{"code":[["MySecretValue"]],"_fndef":true,"_fnparams":[]}],["print","\"Call one: \"",["call","Fn"]],["define","get-secret-value","Fn"],["print","\"Call two: \"",["call",["get-def","get-secret-value"]]]]]
},{}],72:[function(require,module,exports){
module.exports = "% Definitions example\n%\n% Definitions allow one to set keys to value in a top level chain definition\n% dictionary, check if keys are set, get the value of a definition, and get\n% all current definitions.\n% The interpreter and runtime will set various predefined values to give code\n% information about what environment it is running in and what platform\n% libraries have been loaded.\n(\n\t(print \"Definitions:\" (definitions))\n\t(define test true)\n\t(print \"Definitions:\" (definitions))\n\t(if (defined test) (\n\t\t(print \"'test' is defined\")\n\t) (else (\n\t\t(print \"'test' is not defined!\")\n\t)))\n\t(print \"Value of 'test':\" (get-def test))\n\n\t(if (defined 'DEBUG') (\n\t\t(print \"DEBUG mode is on\")\n\t) (else (\n\t\t(print \"DEBUG mode is not on.\")\n\t)))\n\n\t% Assign a callable function to a definition. This is callable by any\n\t% other Lithp function, and is useful for modules that want to provide\n\t% forms of control flow to scripts.\n\t% Modules in general would export functions to the top level chain,\n\t% similar to how the dictionary works.\n\t(var MySecretValue \"A secret value\")\n\t(var Fn # :: (MySecretValue))\n\t(print \"Call one: \" (call Fn))\n\t(define get-secret-value Fn)\n\t(print \"Call two: \" (call (get-def get-secret-value)))\n)";

},{}],73:[function(require,module,exports){
module.exports=[[["def","quote",{"code":[["+",["chr","34"],["get","S"],["chr","34"]]],"_fndef":true,"_fnparams":["S"]}],["var","Str",["+","\"((print \"",["quote","\"Hello world\""],"\"))\""]],["var","Str2",["+","\"((print M) M)\""]],["print","Str"],["eval","Str"],["eval","Str2",["tuple","\"M\"","\"Hello world\""]],["var","S","\"Hello World\""],["eval","\"((print S))\""],["var","Add",["eval",["+","\"((def x #A,B::((+ A B)))(get x/2))\""]]],["print",["call","Add","1","2"]]]]
},{}],74:[function(require,module,exports){
module.exports = "% Demonstrate the eval/1 function which can evaluate Lithp code.\n(\n\t(def quote #S :: (+ (chr 34) (get S) (chr 34)))\n\t(var Str (+ \"((print \" (quote \"Hello world\") \"))\"))\n\t(var Str2 (+ \"((print M) M)\"))\n\t(print Str)\n\t(eval Str)\n\t(eval Str2 (tuple \"M\" \"Hello world\"))\n\t(var S \"Hello World\")\n\t(eval \"((print S))\")\n\t(var Add (eval (+ \"((def x #A,B::((+ A B)))(get x/2))\")))\n\t(print (call Add 1 2))\n)\n";

},{}],75:[function(require,module,exports){
module.exports=[[["platform","ext"],["print","\"Test count: \"",["count-params","1","2","3"]]]]
},{}],76:[function(require,module,exports){
module.exports = "% Demonstrates using extension platforms.\n%\n% Extension platforms add new builtin functions in JavaScript.\n% See the example extension in ext/index.js\n%\n% This will not work in the Web IDE.\n(\n\t% This loads the file ext/index.js as a platform library.\n\t% You could specify other names or paths, but if they contain\n\t% uppercase letters you should quote the name.\n\t(platform ext)\n\t% (platform \"ext\")   % equivalent to above\n\t(print \"Test count: \" (count-params 1 2 3))\n)\n";

},{}],77:[function(require,module,exports){
module.exports=[[["def","fac",{"code":[[["if",["==","0","N"],[["1"]],[["else",[["*","N",["fac",["-","N","1"]]]]]]]]],"_fndef":true,"_fnparams":["N"]}],["var","Test","10"],["print","\"factorial of \"","Test","\": \"",["fac","Test"]]]]
},{}],78:[function(require,module,exports){
module.exports = " % Factorial example. Calculates the factorial of Test.\n(\n\t(def fac #N :: (\n\t\t(if (== 0 N) (\n\t\t\t(1)\n\t\t) ((else (\n\t\t\t(* N (fac (- N 1)))\n\t\t))))\n\t))\n\t(var Test 10)\n\t(print \"factorial of \" Test \": \" (fac Test))\n)\n";

},{}],79:[function(require,module,exports){
module.exports=[[["import","\"lists\""],["var","Mode","caching"],["if",["==","caching","Mode"],[["var","FL",["dict"]],["def","fibFL",{"code":[[["if",["dict-present","FL","N"],[["dict-get","FL","N"]],["else",[["var","I",["fib","N"]],["set","FL",["dict-set","FL","N","I"]],["I"]]]]]],"_fndef":true,"_fnparams":["N"]}],["def","fib",{"code":[[["if",["<","N","2"],["1"],[["+",["fibFL",["-","N","2"]],["fibFL",["-","N","1"]]]]]]],"_fndef":true,"_fnparams":["N"]}],["export-global","fib/1"]],["else",[["def","fib",{"code":[[["if",["<","N","2"],["1"],[["+",["fib",["-","N","1"]],["fib",["-","N","2"]]]]]]],"_fndef":true,"_fnparams":["N"]}],["export-global","fib/1"]]]],["def","fib-orial",{"code":[[["prod",["map",["seq","1","N"],["scope",{"code":[[["fib","I"]]],"_fndef":true,"_fnparams":["I"]}]]]]],"_fndef":true,"_fnparams":["N"]}],["if",["==","caching","Mode"],[["each",["seq","2","20"],["scope",{"code":[[["print",["fib-orial","N"]]]],"_fndef":true,"_fnparams":["N"]}]]],["else",[["print",["fib-orial","15"]]]]]]]
},{}],80:[function(require,module,exports){
module.exports = "% Fib-orial demonstration.\n% This uses caching for a much faster execution time, and forms the basis of what\n% would become the \"cache\" module.\n(\n\t(import \"lists\")\n\t(var Mode caching) % Set to anything else to demonstrate non-caching example\n\n\t% Define the fibonacci sequence, fib/1, based on Mode\n\t(if (== caching Mode) (\n\t\t% This section represents the result cache.\n\t\t(var FL (dict))\n\t\t% A version of fib/1 that checks the results cache (FL)\n\t\t(def fibFL #N :: (\n\t\t\t(if (dict-present FL N) (\n\t\t\t\t(dict-get FL N)\n\t\t\t) (else (\n\t\t\t\t(var I (fib N))\n\t\t\t\t(set FL (dict-set FL N I))\n\t\t\t\t(I))\n\t\t\t))\n\t\t))\n\t\t% And this is the implementation altered to use fibFL lookup.\n\t\t(def fib #N::((if (< N 2) (1) ((+ (fibFL (- N 2)) (fibFL (- N 1)))))))\n\t\t% Export to make available in parent chain\n\t\t(export-global fib/1)\n\t) (else (\n\t\t% This is a direct recursive solution that is incredibly slow.\n\t\t(def fib #N::((if (< N 2) (1) ((+ (fib (- N 1)) (fib (- N 2)))))))\n\t\t% Export to make available in parent chain\n\t\t(export-global fib/1)\n\t)))\n\n\t% This is the fib-orial implmention.\n\t(def fib-orial #N::((prod (map (seq 1 N) (scope #I::((fib I)))))))\n\n\t(if (== caching Mode) (\n\t\t% When caching, we can demonstrate a large number of fast calculations\n\t\t% We call fib-orial with the numbers 2..20 inclusive\n\t\t(each (seq 2 20) (scope #N :: ((print (fib-orial N)))))\n\t) (else (\n\t\t% Non-caching, show a very small calculation - it will likely take longer\n\t\t% than the caching version does in total.\n\t\t(print (fib-orial 15))\n\t)))\n)\n";

},{}],81:[function(require,module,exports){
module.exports=[[["import","lists"],["import","symbols"],["var","Operators",["list","+","-","/","*"]],["var","A","5"],["var","B","10"],["each","Operators",["scope",{"code":[[["print",["+","A","\" \"","Op","\" \"","B","\" = \"",["call-fn","Op","A","B"]]]]],"_fndef":true,"_fnparams":["Op"]}]]]]
},{}],82:[function(require,module,exports){
module.exports = "% Tests applying arbritray functions.\n(\n\t(import lists)\n\t(import symbols)\n\n\t% These are inbuilt operators.\n\t% The symbols module takes care of looking them up based on given arity.\n\t(var Operators (list + - / *))\n\t(var A 5)\n\t(var B 10)\n\t(each Operators (scope #Op :: (\n\t\t(print (+ A \" \" Op \" \" B \" = \" (call-fn Op A B)))\n\t)))\n)\n";

},{}],83:[function(require,module,exports){
module.exports=[[["def","for",{"code":[[["var","Index","0"],["var","ForInner",["scope",{"code":[[["print","\"Running callback for \"","Index","\" on \"","Head"],["call","Callback","Head","Index"],["set","Index",["+","1","Index"]],["if",["!=","0",["length","Tail"]],[["call","ForInner",["head","Tail"],["tail","Tail"]]]]]],"_fndef":true,"_fnparams":["Head","Tail"]}]],["call","ForInner",["head","List"],["tail","List"]]]],"_fndef":true,"_fnparams":["List","Callback"]}],["for",["list","1","2","3"],{"code":[[["print","\"Element at index \"","Index","\": \"","Element"]]],"_fndef":true,"_fnparams":["Element","Index"]}]]]
},{}],84:[function(require,module,exports){
module.exports = "% A for loop example.\n% This functionality will be moved to a module at some point.\n(\n\t(def for #List,Callback :: (\n\t\t(var Index 0)\n\t\t(var ForInner (scope #Head,Tail :: (\n\t\t\t(print \"Running callback for \" Index \" on \" Head)\n\t\t\t(call Callback Head Index)\n\t\t\t(set Index (+ 1 Index))\n\t\t\t(if (!= 0 (length Tail)) (\n\t\t\t\t(call ForInner (head Tail) (tail Tail))\n\t\t\t))\n\t\t)))\n\t\t(call ForInner (head List) (tail List))\n\t))\n\t(for (list 1 2 3) #Element,Index :: (\n\t\t(print \"Element at index \" Index \": \" Element)\n\t))\n)\n";

},{}],85:[function(require,module,exports){
module.exports=[[["import","lists"],["import","math"],["def","isSquare",{"code":[[["var","S",["parse-int",["+",["sqrt","V"],"0.5"]]],["==",["*","S","S"],"V"]]],"_fndef":true,"_fnparams":["V"]}],["var","MedianCache",["dict"]],["def","isMedian",{"code":[[["if",["dict-present","MedianCache","V"],[["dict-get","MedianCache","V"]],[["var","Result",["and",["==","0",["@","V","4"]],["isSquare",["round",["/","V","4"]]]]],["dict-set","MedianCache","V","Result"],["Result"]]]]],"_fndef":true,"_fnparams":["V"]}],["def","main",{"code":[[["var","NTri","0"],["each",["seq","1","N"],["scope",{"code":[[["each",["seq",["round",["/",["+","C","1"],"2"]],"C"],["scope",{"code":[[["each",["seq",["+",["-","C","B"],"1"],"B"],["scope",{"code":[[["var","Test3",["+",["*","A","A"],["*","B","B"]]],["var","Test3",["-",["*","2","Test3"],["*","C","C"]]],["if",["isMedian","Test3"],[["set","NTri",["+","NTri","1"]]],[["var","Test2",["+",["*","A","A"],["*","C","C"]]],["var","Test2",["-",["*","2","Test2"],["*","B","B"]]],["if",["isMedian","Test2"],[["set","NTri",["+","NTri","1"]]],[["var","Test1",["+",["*","B","B"],["*","C","C"]]],["var","Test1",["-",["*","2","Test1"],["*","A","A"]]],["if",["isMedian","Test1"],[["set","NTri",["+","NTri","1"]]]]]]]]]],"_fndef":true,"_fnparams":["A"]}]]]],"_fndef":true,"_fnparams":["B"]}]]]],"_fndef":true,"_fnparams":["C"]}]],["NTri"]]],"_fndef":true,"_fnparams":["N"]}],["print",["main","20"]]]]
},{}],86:[function(require,module,exports){
module.exports = "% A work-in-progress entry for a Codegolf challenge:\n% http://codegolf.stackexchange.com/questions/53100/integral-triangles-and-integral-medians\n(\n\t(import lists)\n\t(import math)\n\n\t(def isSquare #V :: (\n\t\t(var S (parse-int (+ (sqrt V) 0.5)))\n\t\t% (print \"isSquare - V:\" V \" S: \" S \", S*S: \" (* S S))\n\t\t(== (* S S) V)\n\t))\n\n\t(var MedianCache (dict))\n\t(def isMedian #V :: (\n\t\t(if (dict-present MedianCache V) (\n\t\t\t(dict-get MedianCache V)\n\t\t) (\n\t\t\t% (print \"isMedian \" V \", % 4=\" (@ V 4))\n\t\t\t(var Result (and (== 0 (@ V 4)) (isSquare (round (/ V 4)))))\n\t\t\t(dict-set MedianCache V Result)\n\t\t\t(Result)\n\t\t))\n\t))\n\n\t(def main #N :: (\n\t\t(var NTri 0)\n\t\t(each (seq 1 N) (scope #C :: (\n\t\t\t(each (seq (round (/ (+ C 1) 2)) C) (scope #B :: (\n\t\t\t\t(each (seq (+ (- C B) 1) B) (scope #A :: (\n\t\t\t\t\t% (print \"A: \" A \" B: \" B \" C: \" C)\n\t\t\t\t\t(var Test3 (+ (* A A) (* B B)))\n\t\t\t\t\t(var Test3 (- (* 2 Test3) (* C C)))\n\t\t\t\t\t(if (isMedian Test3) (\n\t\t\t\t\t\t(set NTri (+ NTri 1))\n\t\t\t\t\t) (\n\t\t\t\t\t\t(var Test2 (+ (* A A) (* C C)))\n\t\t\t\t\t\t(var Test2 (- (* 2 Test2) (* B B)))\n\t\t\t\t\t\t(if (isMedian Test2) (\n\t\t\t\t\t\t\t(set NTri (+ NTri 1))\n\t\t\t\t\t\t) (\n\t\t\t\t\t\t\t(var Test1 (+ (* B B) (* C C)))\n\t\t\t\t\t\t\t(var Test1 (- (* 2 Test1) (* A A)))\n\t\t\t\t\t\t\t(if (isMedian Test1) (\n\t\t\t\t\t\t\t\t(set NTri (+ NTri 1))\n\t\t\t\t\t\t\t))\n\t\t\t\t\t\t))\n\t\t\t\t\t))\n\t\t\t\t)))\n\t\t\t)))\n\t\t)))\n\t\t(NTri)\n\t))\n\n\t(print (main 20))\n)\n";

},{}],87:[function(require,module,exports){
module.exports=[[["def","f",{"code":[[["invoke","P","\"map\"",["js-bridge",{"code":[["replace","W",["regex","\".\"","\"g\""],["js-bridge",{"code":[["index",["index","P",["&",["+","I","J"],"1"]],"J"]],"_fndef":true,"_fnparams":["C","J"]}]]],"_fndef":true,"_fnparams":["W","I"]}]]]],"_fndef":true,"_fnparams":["P"]}],["def","f",{"code":[[["invoke","P","\"map\"",["js-bridge",{"code":[["replace","W",["regex","\".\"","\"g\""],["js-bridge",{"code":[["index",["index","P",["&",["+","I","J"],"1"]],"J"]],"_fndef":true,"_fnparams":["C","J"]}]]],"_fndef":true,"_fnparams":["W","I"]}]]]],"_fndef":true,"_fnparams":["P"]}],["print",["f",["list","\"Hello,\"","\"world!\""]]]]]
},{}],88:[function(require,module,exports){
module.exports = "% An entry for a code golf challenge.\n(\n\t% Readable version:\n\t(def f #P :: (\n\t\t(invoke P \"map\" (js-bridge #W,I ::\n\t\t\t(replace W (regex \".\" \"g\") (js-bridge #C,J ::\n\t\t\t\t(index (index P (& (+ I J) 1)) J)\n\t\t\t))\n\t\t))\n\t))\n\t% Golfed version (now out of date):\n\t(def f #P::((invoke P \"map\" (js-bridge #W,I::(replace W (regex \".\" \"g\") (js-bridge #C,J::(index (index P (& (+ I J) 1)) J)))))))\n\t(print (f (list \"Hello,\" \"world!\")))\n)\n";

},{}],89:[function(require,module,exports){
module.exports=[[["def","i",{"code":[[["replace","S",["regex","\"\\\\d\"","\"g\""],["js-bridge",{"code":[[["^","X","1"]]],"_fndef":true,"_fnparams":["X"]}]]]],"_fndef":true,"_fnparams":["S"]}],["print",["i","\"01010101111000\""]]]]
},{}],90:[function(require,module,exports){
module.exports = "% An entry for a code-golf challenge involving inversing a binary number.\n% Uses js-bridge due to lack of inbuilt regex replace function.\n(\n\t(def i #S::((replace S (regex \"\\\\d\" \"g\") (js-bridge #X::((^ X 1))))))\n\t(print (i \"01010101111000\"))\n)\n";

},{}],91:[function(require,module,exports){
module.exports=[[["def","map",{"code":[[["var","Result",["list"]],["var","MapInner",["scope",{"code":[[["set","Result",["++","Result",["call","Callback","Head"]]],["if",["!=","0",["length","Tail"]],[["call","MapInner",["head","Tail"],["tail","Tail"]]]]]],"_fndef":true,"_fnparams":["Head","Tail"]}]],["call","MapInner",["head","List"],["tail","List"]],["Result"]]],"_fndef":true,"_fnparams":["List","Callback"]}],["print",["map",["list","1","2","3"],{"code":[[["+","N","1"]]],"_fndef":true,"_fnparams":["N"]}]],["print",["map",["list","1","2","3"],{"code":[[["*","N","2"]]],"_fndef":true,"_fnparams":["N"]}]]]]
},{}],92:[function(require,module,exports){
module.exports = "% Map a list with a callback.\n% This functionality will be moved to a module at some point.\n(\n\t(def map #List,Callback :: (\n\t\t(var Result (list))\n\t\t(var MapInner (scope #Head,Tail :: (\n\t\t\t(set Result (++ Result (call Callback Head)))\n\t\t\t(if (!= 0 (length Tail)) (\n\t\t\t\t(call MapInner (head Tail) (tail Tail))\n\t\t\t))\n\t\t)))\n\t\t(call MapInner (head List) (tail List))\n\t\t(Result)\n\t))\n\t(print (map (list 1 2 3) #N :: ((+ N 1))))\n\t(print (map (list 1 2 3) #N :: ((* N 2))))\n)";

},{}],93:[function(require,module,exports){
module.exports=[[["import","\"file\""],["import","\"lists\""],["import","\"readline\""],["var","TabIndentCount","4"],["var","TabIndent",["invoke","\" \"","repeat","TabIndentCount"]],["def","make-template",{"code":[[["var","Header","\"##[Lithp][1],\""],["var","Url","\"  [1]: https://github.com/andrakis/node-lithp\""],["print","Header",["length","Code"],"\"bytes\""],["print"],["var","Test",["match","Code",["regex",["nl"],"\"g\""]]],["if",["<=",["length",["?",["==",["null"],"Test"],"[]","Test"]],"1"],[["print","\"    \"","Code"]],["else",[["each",["list",["tuple","\"\\\\t\"","TabIndent"]],["scope",{"code":[[["set","Code",["replace","Code",["regex",["index","Tuple","0"],"\"g\""],["index","Tuple","1"]]]]],"_fndef":true,"_fnparams":["Tuple"]}]],["var","Lines",["split","Code",["regex","\"\\r?\\n\\r?\""]]],["each","Lines",["scope",{"code":[[["print",["+","TabIndent","Line"]]]],"_fndef":true,"_fnparams":["Line"]}]]]]],["print"],["print","Url"]]],"_fndef":true,"_fnparams":["Code"]}],["if",["==","false",["get-def","\"FILE\""]],[["readline","\"Code: \"",["scope",{"code":[[["make-template","Code"]]],"_fndef":true,"_fnparams":["Code"]}]]],["else",[["var","File",["+","\"\"",["get-def","\"FILE\""]]],["print","\"Opening file\"","File","\"...\""],["read-file","File",["scope",{"code":[[["if",["!=",["null"],"Err"],[["print","\"Got Err:\"","Err"]],["else",[["var","Content",["to-string","Data"]],["make-template","Content"]]]]]],"_fndef":true,"_fnparams":["Err","Data"]}]]]]]]]
},{}],94:[function(require,module,exports){
module.exports = "% Markdown Template\n% This creates a Markdown template for sample Lithp code for an answer\n% to a code-golf challenge. It includes a correct link to the language\n% Github page, as well as a count of characters and correct indentation\n% for markup.\n(\n\t(import \"file\")\n\t(import \"lists\")\n\t(import \"readline\")\n\n\t(var TabIndentCount 4)\n\t(var TabIndent (invoke \" \" repeat TabIndentCount))\n\n\t(def make-template #Code :: (\n\t\t(var Header \"##[Lithp][1],\")\n\t\t(var Url    \"  [1]: https://github.com/andrakis/node-lithp\")\n\t\t(print Header (length Code) \"bytes\")\n\t\t(print)\n\t\t(var Test (match Code (regex (nl) \"g\")))\n\t\t(if (<= (length (? (== (null) Test) [] Test)) 1) (\n\t\t\t(print \"    \" Code)\n\t\t) (else (\n\t\t\t(each (list (tuple \"\\\\t\" TabIndent)) (scope #Tuple :: (\n\t\t\t\t(set Code (replace Code (regex (index Tuple 0) \"g\") (index Tuple 1)))\n\t\t\t)))\n\t\t\t(var Lines (split Code (regex \"\\r?\\n\\r?\")))\n\t\t\t(each Lines (scope #Line :: ((print (+ TabIndent Line)))))\n\t\t)))\n\t\t(print)\n\t\t(print Url)\n\t))\n\n\t(if (== false (get-def \"FILE\")) (\n\t\t(readline \"Code: \" (scope #Code :: (\n\t\t\t(make-template Code)\n\t\t)))\n\t) (else (\n\t\t(var File (+ \"\" (get-def \"FILE\")))\n\t\t(print \"Opening file\" File \"...\")\n\t\t(read-file File (scope #Err,Data :: (\n\t\t\t(if (!= (null) Err) (\n\t\t\t\t(print \"Got Err:\" Err)\n\t\t\t) (else (\n\t\t\t\t(var Content (to-string Data))\n\t\t\t\t(make-template Content)\n\t\t\t)))\n\t\t)))\n\t)))\n)\n";

},{}],95:[function(require,module,exports){
module.exports=[[["var","Path",["+",["get-def","__dirname"],"\"/module_lib\""]],["print","\"Path to module-lib:\"","Path"],["try",[["import","Path"]],["catch",{"code":[[["import","\"samples/module_lib\""]]],"_fndef":true,"_fnparams":[]}]],["print","\"Add 2+2:\"",["add","2","2"]],["var","Add5",["add","5"]],["print","\"Add 5+2:\"",["call","Add5","2"]],["print","\"Module value:\"",["getMyValue"]],["var","MyValue","1"],["print","\"Call with two:\"",["callWith2",{"code":[[["+","MyValue","Two"]]],"_fndef":true,"_fnparams":["Two"]}]]]]
},{}],96:[function(require,module,exports){
module.exports = "% Test importing a module into the current closure.\n(\n\t% Calculate correct path to the module, module_lib.\n\t% The .lithp extension is not required.\n\t(var Path (+ (get-def __dirname) \"/module_lib\"))\n\t(print \"Path to module-lib:\" Path)\n\n\t% This brings all exported module functions into the current scope.\n\t(try (\n\t\t(import Path)\n\t) (catch # :: (\n\t\t(import \"samples/module_lib\")\n\t)))\n\n\t% Call a module function.\n\t(print \"Add 2+2:\" (add 2 2))\n\n\t% Use a local variable to demonstrate module scoping.\n\t(var Add5 (add 5))\n\t(print \"Add 5+2:\" (call Add5 2))\n\n\t% Call a module function that returns a module local variable value to\n\t% demonstrate module scoping further.\n\t(print \"Module value:\" (getMyValue))\n\n\t% Call a function by providing a callback. This callback retains access\n\t% to the current script scope, allowing it to refer to currently defined\n\t% variables and functions.\n\t(var MyValue 1)\n\t(print \"Call with two:\" (callWith2 #Two :: ((+ MyValue Two))))\n\n\t% This function is defined in the module, but not exported.\n\t% Uncommenting the following line would cause the script to crash:\n\t%(private_function 4 2)\n)\n";

},{}],97:[function(require,module,exports){
module.exports=[[["def","add",{"code":[[["scope",{"code":[[["+","A","B"]]],"_fndef":true,"_fnparams":["B"]}]]],"_fndef":true,"_fnparams":["A"]}],["def","add",{"code":[[["+","A","B"]]],"_fndef":true,"_fnparams":["A","B"]}],["export","add/1","add/2"],["var","MyValue","1"],["def","getMyValue",{"code":[["MyValue"]],"_fndef":true,"_fnparams":[]}],["var","Two","2"],["def","callWith2",{"code":[[["call","Fn","Two"]]],"_fndef":true,"_fnparams":["Fn"]}],["export","getMyValue/0","callWith2/1"],["def","private_function",{"code":[[["-","A","B"]]],"_fndef":true,"_fnparams":["A","B"]}]]]
},{}],98:[function(require,module,exports){
module.exports = "% This is an example module, designed to be used with module.lithp.\n(\n\t% Define some functions to export\n\t(def add #A :: (\n\t\t(scope #B :: ((+ A B)))\n\t))\n\t(def add #A,B :: ((+ A B)))\n\n\t% Export desired functions\n\t(export add/1 add/2)\n\n\t% Define a local variable to demonstrate correct scoping.\n\t(var MyValue 1)\n\t(def getMyValue # :: (MyValue))\n\n\t% This example takes a function, and adds a local variable to it.\n\t% The file module.lithp demonstrates that variables correctly\n\t% resolve.\n\t(var Two 2)\n\t(def callWith2 #Fn :: ((call Fn Two)))\n\n\t% Export our two scoping functions.\n\t(export getMyValue/0 callWith2/1)\n\n\t% Note that any function not exported will not be available to\n\t% the module importing. Only functions specified to export will\n\t% be exported.\n\t(def private_function #A,B :: ((- A B)))\n)\n";

},{}],99:[function(require,module,exports){
module.exports=[[["def","f",{"code":[[["if",["<","N","2"],[["?",["!=","0","N"],["*","2","R"],"1"]],[["/",["*",["*",["*",["*",["f",["-","N","2"],"R"],"2"],["pi"]],"R"],"R"],"N"]]]]],"_fndef":true,"_fnparams":["N","R"]}],["print",["f","1","1"]],["print",["f","2","3"]],["print",["f","3","1"]],["print",["f","3","4.5"]],["print",["f","1","9.379"]],["print",["f","0","48"]]]]
},{}],100:[function(require,module,exports){
module.exports = "% An entry for a code-golf challenge. Now much out of date due to parser improvements.\n(\n\t(def f #N,R::((if (< N 2) ((? (!= 0 N) (* 2 R) 1)) ((/ (* (* (* (* (f (- N 2) R) 2) (pi)) R) R) N)))))\n\t(print (f 1 1))\n\t(print (f 2 3))\n\t(print (f 3 1))\n\t(print (f 3 4.5))\n\t(print (f 1 9.379))\n\t(print (f 0 48))\n)\n";

},{}],101:[function(require,module,exports){
module.exports=[[["def","odd",{"code":[[["var","Split",["split","S",["regex","\"[aeiou]\"","\"i\""]]],["if",["==","1",["&","1",["~",["length","Split"]]]],[["\"odd\""]],["else",[["\"even\""]]]]]],"_fndef":true,"_fnparams":["S"]}],["def","test",{"code":[[["print","\"Test \"",["quote","S"],"\": \"",["odd","S"]]]],"_fndef":true,"_fnparams":["S"]}],["test","\"trees\""],["test","\"brush\""],["test","\"CAts\""],["test","\"Savoie\""],["test","\"rhythm\""]]]
},{}],102:[function(require,module,exports){
module.exports = "% A valid solution to a Programming Puzzle and Code Golf post:\n% http://codegolf.stackexchange.com/questions/93906/is-it-an-odd-word\n%\n% However, it is ineligible for competing, since the majority of the\n% functionality required was implemented after the challenge was posted.\n% In fact, at the time the challenge was posted, no parser existed.\n% Approximately 10 days later the parser was finished and parsing this\n% file correctly.\n(\n\t% Golfed:\n\t% (def odd #S::((if (== 1 (& 1 (~ (length (split S (regex \"[aeiou]\" \"i\"))))))(\"odd\")(\"even\"))))\n\t% Ungolfed:\n\t(def odd #S::(\n\t\t(var Split (split S (regex \"[aeiou]\" \"i\")))\n\t\t(if (== 1 (& 1 (~ (length Split)))) (\n\t\t\t(\"odd\")\n\t\t) (else (\n\t\t\t(\"even\")))\n\t\t)\n\t))\n\t(def test #S :: (\n\t\t(print \"Test \" (quote S) \": \" (odd S))\n\t))\n\t(test \"trees\")    % even\n\t(test \"brush\")    % odd\n\t(test \"CAts\")     % odd\n\t(test \"Savoie\")   % even\n\t(test \"rhythm\")   % even\n)\n\n";

},{}],103:[function(require,module,exports){
module.exports=[[["import","\"lists\""],["def","f",{"code":[[["each",["seq","1","10"],{"code":[[["print","N"]]],"_fndef":true,"_fnparams":["N"]}]]],"_fndef":true,"_fnparams":[]}],["def","x",{"code":[[["def","y",{"code":[[["print","N"],["if",["<","N","10"],[["y",["+","N","1"]]]]]],"_fndef":true,"_fnparams":["N"]}],["y","1"]]],"_fndef":true,"_fnparams":[]}],["f"]]]
},{}],104:[function(require,module,exports){
module.exports = "% A solution to a code-golf challenge to print numbers 1 - 10.\n% Included are two different solutions, one importing a module and\n% the other attempting a recusrive implementation.\n% The module version ended up shorter entirely.\n(\n\t(import \"lists\")(def f #::((each (seq 1 10) #N::((print N)))))\n\t(def x #::((def y #N::((print N)(if (< N 10) ((y (+ N 1))))))(y 1)))\n\t(f)\n)\n";

},{}],105:[function(require,module,exports){
module.exports=[[["def","f",{"code":[[["?",["!=",["null"],["match","S","\"^((.+)\\\\2)+$\""]],"true","false"]]],"_fndef":true,"_fnparams":["S"]}],["print",["f","\"aa\""]],["print",["f","\"aabaaababbbaba\""]],["print",["f","\"aaababbabbabbbababbaabaabaababaaba\""]],["print",["f","\"ba\""]]]]
},{}],106:[function(require,module,exports){
module.exports = "% An entry for a code-golf challenge about pairable strings.\n(\n\t(def f #S::((? (!= (null) (match S \"^((.+)\\\\2)+$\")) true false)))\n\t(print (f \"aa\"))\n\t(print (f \"aabaaababbbaba\"))\n\t(print (f \"aaababbabbabbbababbaabaabaababaaba\"))\n\t(print (f \"ba\"))\n)\n";

},{}],107:[function(require,module,exports){
module.exports=[[["def","f",{"code":[[["def","x",{"code":[["invoke","S","repeat","N"]],"_fndef":true,"_fnparams":["S","N"]}],["var","A",["x","\"/\"","5"]],["var","B",["x","\"\\\\\"","5"]],["var","C",["+",["x",["+","A","B"],"6"],["nl"]]],["var","D",["+",["x",["+","B","A"],"6"],["nl"]]],["print",["x",["+",["x","C","4"],["x","D","4"]],"5"]]]],"_fndef":true,"_fnparams":[]}],["f"]]]
},{}],108:[function(require,module,exports){
module.exports = "% An entry for a code-golf challenge about rendering a nice pillow.\n(\n\t(def f #::((def x #S,N::(invoke S repeat N))(var A(x \"/\" 5))(var B(x \"\\\\\" 5))(var C(+(x(+ A B) 6)(nl)))(var D(+(x(+ B A) 6)(nl)))(print(x(+(x C 4)(x D 4)) 5))))\n\t(f)\n)\n";

},{}],109:[function(require,module,exports){
module.exports=[[["def","pow",{"code":[[["if",["==","Y","1"],["get","X"],["else",[["*","X",["pow","X",["-","Y","1"]]]]]]]],"_fndef":true,"_fnparams":["X","Y"]}],["var","A","5"],["var","B","100"],["print","\"\"","A","\" to the power of \"","B","\":\"",["pow","A","B"]]]]
},{}],110:[function(require,module,exports){
module.exports = "% Demonstrate a power function\n(\n\t(def pow #X,Y :: (\n\t\t(if (== Y 1)\n\t\t\t% TODO: Parser bug\n\t\t\t% X\n\t\t\t(get X)\n\t\t(else (\n\t\t\t(* X (pow X (- Y 1)))\n\t\t)))\n\t))\n\t(var A 5)\n\t(var B 100)\n\t(print \"\" A \" to the power of \" B \":\" (pow A B))\n)\n";

},{}],111:[function(require,module,exports){
module.exports=[[["def","f",{"code":[[["replace","X",["regex","\"([aeiou]+[^aeiou]*){1,2} [^aeiou]*\""],"\"\""]]],"_fndef":true,"_fnparams":["X"]}],["print",["f","\"brad angelina\""]]]]
},{}],112:[function(require,module,exports){
module.exports = "% A valid solution to the programming puzzle:\n%  http://codegolf.stackexchange.com/questions/94534/progruzzle-colf\n(\n\t(def f #X::((replace X (regex \"([aeiou]+[^aeiou]*){1,2} [^aeiou]*\") \"\")))\n\t(print (f \"brad angelina\"))\n)\n";

},{}],113:[function(require,module,exports){
module.exports=[[["platform","v1"],["var","Fs",["require","\"fs\""]],["var","SampleFile",["+",["get-def","__dirname"],"\"/../index.js\""]],["var","FsReadFileSync",["dict-get","Fs","\"readFileSync\""]],["print","\"readFileSync:\"",["inspect","FsReadFileSync"]],["print","\"Read index.js:\"",["call","FsReadFileSync","SampleFile"]],["var","FsReadFile",["dict-get","Fs","\"readFile\""]],["print","\"readFile:\"",["inspect","FsReadFile"]],["var","Our_callback",["js-bridge",{"code":[[["if",["!=",["null"],"Err"],[["print","\"Failed to read file, err:  \"","Err"]],["else",[["print","\"Data from file:\""],["print",["invoke","Data","\"toString\""]]]]]]],"_fndef":true,"_fnparams":["Err","Data"]}]],["call","FsReadFile","SampleFile","Our_callback"],["call","FsReadFile","\"non-existant\"","Our_callback"]]]
},{}],114:[function(require,module,exports){
module.exports = "% Demonstrate reading a file using node builtins\n%\n(\n\t% The require/1 function requires Platform V1 functionality.\n\t% This will load it if not already loaded with the '-v1' flag.\n\t(platform v1)\n\t(var Fs (require \"fs\"))\n\n\t% Use the definitions table to get the path to the example file we will use.\n\t(var SampleFile (+ (get-def __dirname) \"/../index.js\"))\n\n\t% Use the readFileSync method directly\n\t(var FsReadFileSync (dict-get Fs \"readFileSync\"))\n\t(print \"readFileSync:\" (inspect FsReadFileSync))\n\t% You can call FsReadFileSync using call/* (a standard builtin.)\n\t(print \"Read index.js:\" (call FsReadFileSync SampleFile))\n\n\t% Now test using a callback and readFile\n\t(var FsReadFile (dict-get Fs \"readFile\"))\n\t(print \"readFile:\" (inspect FsReadFile))\n\n\t% js-bridge returns a native JavaScript function that, when called, invokes\n\t% the lithp interpreter with the given function definition, and sets all\n\t% provided parametes. Allows you to provide callbacks to JavaScript\n\t% functions as used below.\n\t(var Our_callback (js-bridge #Err,Data :: (\n\t\t(if (!= (null) Err) (\n\t\t\t(print \"Failed to read file, err:  \" Err)\n\t\t) (else (\n\t\t\t(print \"Data from file:\")\n\t\t\t(print (invoke Data \"toString\"))\n\t\t)))\n\t)))\n\t% You can call FsReadFile using call/* (a standard builtin.)\n\t(call FsReadFile SampleFile Our_callback)\n\t(call FsReadFile \"non-existant\" Our_callback)\n)\n\n";

},{}],115:[function(require,module,exports){
module.exports=[[["def","fac-recursive",{"code":[[["def","fac-r-inner",{"code":[[["if",["==","0","N"],[["Acc"]],["else",[["recurse",["-","N","1"],["*","N","Acc"]]]]]]],"_fndef":true,"_fnparams":["N","Acc"]}],["fac-r-inner","N","1"]]],"_fndef":true,"_fnparams":["N"]}],["print",["fac-recursive","100"]]]]
},{}],116:[function(require,module,exports){
module.exports = "% Sample: recurse\n%\n% Purpose: Demonstrate tail recursion via the recurse/* builtin.\n%\n% Notes:   You must provide the function name of the function you\n%          wish to recurse. Presently this cannot be detected.\n%\n%          Also note that the stack depth remains constant when run\n%          with the debug flag (-d).\n(\n\t(def fac-recursive #N :: (\n\t\t(def fac-r-inner #N,Acc :: (\n\t\t\t(if (== 0 N) (\n\t\t\t\t(Acc)\n\t\t\t) (else (\n\t\t\t\t(recurse (- N 1) (* N Acc))\n\t\t\t)))\n\t\t))\n\t\t(fac-r-inner N 1)\n\t))\n\n\t(print (fac-recursive 100))\n)\n";

},{}],117:[function(require,module,exports){
module.exports=[[["def","add",{"code":[[["scope",{"code":[[["+","A","B"]]],"_fndef":true,"_fnparams":["B"]}]]],"_fndef":true,"_fnparams":["A"]}],["var","Add5",["add","5"]],["var","Add10",["add","10"]],["var","N","10"],["print","\"Add5 with \"","N","\": \"",["call","Add5","N"]],["print","\"Add10 with \"","N","\": \"",["call","Add10","N"]],["assert",["==","15",["call","Add5","10"]]]]]
},{}],118:[function(require,module,exports){
module.exports = "% Tests variable scoping.\n% Allows returned anonymous functions (which can be called) to retain access\n% to parameters it had when it was called.\n% Each call generates a new unique scope, parented to the scope that\n% contained the parameters. This is provides functionality similar to how\n% JavaScript closures work.\n(\n\t% add/1 is a function that returns a scoped FunctionDefinition also of airty\n\t% that can be called to add the two numbers together.\n\t(def add #A :: (\n\t\t% scope/1 is a library function that ties the given anonymous function\n\t\t% to the call scope it was called in, allowing variables to be retained.\n\t\t(scope #B :: ((+ A B)))\n\t))\n\t(var Add5 (add 5))\n\t(var Add10 (add 10))\n\t(var N 10)\n\t(print \"Add5 with \" N \": \" (call Add5 N))\n\t(print \"Add10 with \" N \": \" (call Add10 N))\n\t(assert (== 15 (call Add5 10)))\n)\n";

},{}],119:[function(require,module,exports){
arguments[4][77][0].apply(exports,arguments)
},{"dup":77}],120:[function(require,module,exports){
module.exports = "% Test shorthand expressions, that is with a minimum amount of spaces.\n(\n\t(def fac #N::((if(== 0 N)((1))((else((* N(fac(- N 1)))))))))\n\t(var Test 10)\n\t(print \"factorial of \" Test \": \" (fac Test))\n)\n";

},{}],121:[function(require,module,exports){
module.exports=[[["print","\"Hello, world!\""],["print","\"1+1:\"",["+","1","1"],"\" Wow!\""],["print","\"Also a test:\"",["*","5","10"]],["print","\"One last test:\"",["/","10","2"]],["var","A","5"],["var","B","6"],["print","\"A+B:\"",["+","A","B"]]]]
},{}],122:[function(require,module,exports){
module.exports = "(\n    % Print a simple message\n    (print  \"Hello, world!\")\n\t% Print some more messages using simple function calls\n    (print \"1+1:\" (+ 1 1) \" Wow!\")\n    (print \"Also a test:\" (* 5 10))\n\t(print \"One last test:\" (/ 10 2))\n\t% Print the result of a calculation of two variables\n\t(var A 5)\n\t(var B 6)\n\t(print \"A+B:\" (+ A B))\n)\n";

},{}],123:[function(require,module,exports){
module.exports=[[["import","\"lists\""],["def","s",{"code":[[["var","X",["repeat","\"#\"","N"]],["print","X"],["each",["seq","3","N"],["scope",{"code":[[["print",["+","\"#\"",["repeat","\" \"",["-","N","2"]],"\"#\""]]]],"_fndef":true,"_fnparams":["X"]}]],["print","X"]]],"_fndef":true,"_fnparams":["N"]}],["s","10"]]]
},{}],124:[function(require,module,exports){
module.exports = "% An entry for a code-golf challenge. A few bytes could be shaved off now.\n% Prints a square of the given size (in the example below, 10 characters wide.)\n% Doesn't look correct on most fonts, though.\n(\n\t(import \"lists\")\n\t(def s #N::((var X (repeat \"#\" N))(print X)(each (seq 3 N) (scope #X::((print (+ \"#\" (repeat \" \" (- N 2)) \"#\")))))(print X)))\n\t(s 10)\n)\n";

},{}],125:[function(require,module,exports){
module.exports=[[["var","A","5"],["var","B","6"],["print","\"A+B:\"",["+","A","B"]],["if",["==","A","B"],[["print","\":)\""],["print","\"The same!\""]],["else",[["print","\":(\""],["print","\"Different\""]]]]]]
},{}],126:[function(require,module,exports){
module.exports = "% Simple subchain test. Subchains are passed to the if/3 function and evaluated\n% if the test is Atom('true').\n(\n\t(var A 5)\n\t(var B 6)\n\t(print \"A+B:\" (+ A B))\n\t(if (== A B) (\n\t\t(print \":)\")\n\t\t(print \"The same!\")\n\t) (else (\n\t\t(print \":(\")\n\t\t(print \"Different\")\n\t)))\n)\n";

},{}],127:[function(require,module,exports){
module.exports=[[["def","count-args/*",{"code":[[["print","\"Args length: \"",["length","Args"]]]],"_fndef":true,"_fnparams":["Args"]}],["count-args","foo","bar","yeah"]]]
},{}],128:[function(require,module,exports){
module.exports = "% Test functions with unlimited arguments\n(\n\t(def count-args/* #Args :: (\n\t\t(print \"Args length: \" (length Args))\n\t))\n\t(count-args foo bar yeah)\n)\n";

},{}],129:[function(require,module,exports){
module.exports=[[["def","x",{"code":[[["print",["replace",["repeat","\"_|__\"","175"],["regex","\"(.{70})\"","\"g\""],"\"$1\\n\""]]]],"_fndef":true,"_fnparams":[]}],["x"]]]
},{}],130:[function(require,module,exports){
module.exports = "% An entry for a code-golf challenge.\n% Displays an ASCII brick wall.\n(\n\t(def x #::((print (replace (repeat \"_|__\" 175) (regex \"(.{70})\" \"g\") \"$1\\n\"))))\n\t(x)\n)\n";

},{}],131:[function(require,module,exports){
module.exports=[[["def","seq2",{"code":[[["var","L",["list"]],["while",[["<","A","B"]],[["set","L",["++","L",["list","A"]]],["set","A",["+","A","1"]]]],"L"]],"_fndef":true,"_fnparams":["A","B"]}],["print",["seq2","1","10"]]]]
},{}],132:[function(require,module,exports){
module.exports = "(\n\t% Updated seq\n\t(def seq2 #A,B :: (\n\t\t(var L (list))\n\t\t(while ((< A B)) (\n\t\t\t(set L (++ L (list A)))\n\t\t\t(set A (+ A 1))\n\t\t))\n\t\tL\n\t))\n\t(print (seq2 1 10))\n)\n";

},{}],133:[function(require,module,exports){
(function (process){
// Copyright Joyent, Inc. and other Node contributors.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.

// resolves . and .. elements in a path array with directory names there
// must be no slashes, empty elements, or device names (c:\) in the array
// (so also no leading and trailing slashes - it does not distinguish
// relative and absolute paths)
function normalizeArray(parts, allowAboveRoot) {
  // if the path tries to go above the root, `up` ends up > 0
  var up = 0;
  for (var i = parts.length - 1; i >= 0; i--) {
    var last = parts[i];
    if (last === '.') {
      parts.splice(i, 1);
    } else if (last === '..') {
      parts.splice(i, 1);
      up++;
    } else if (up) {
      parts.splice(i, 1);
      up--;
    }
  }

  // if the path is allowed to go above the root, restore leading ..s
  if (allowAboveRoot) {
    for (; up--; up) {
      parts.unshift('..');
    }
  }

  return parts;
}

// Split a filename into [root, dir, basename, ext], unix version
// 'root' is just a slash, or nothing.
var splitPathRe =
    /^(\/?|)([\s\S]*?)((?:\.{1,2}|[^\/]+?|)(\.[^.\/]*|))(?:[\/]*)$/;
var splitPath = function(filename) {
  return splitPathRe.exec(filename).slice(1);
};

// path.resolve([from ...], to)
// posix version
exports.resolve = function() {
  var resolvedPath = '',
      resolvedAbsolute = false;

  for (var i = arguments.length - 1; i >= -1 && !resolvedAbsolute; i--) {
    var path = (i >= 0) ? arguments[i] : process.cwd();

    // Skip empty and invalid entries
    if (typeof path !== 'string') {
      throw new TypeError('Arguments to path.resolve must be strings');
    } else if (!path) {
      continue;
    }

    resolvedPath = path + '/' + resolvedPath;
    resolvedAbsolute = path.charAt(0) === '/';
  }

  // At this point the path should be resolved to a full absolute path, but
  // handle relative paths to be safe (might happen when process.cwd() fails)

  // Normalize the path
  resolvedPath = normalizeArray(filter(resolvedPath.split('/'), function(p) {
    return !!p;
  }), !resolvedAbsolute).join('/');

  return ((resolvedAbsolute ? '/' : '') + resolvedPath) || '.';
};

// path.normalize(path)
// posix version
exports.normalize = function(path) {
  var isAbsolute = exports.isAbsolute(path),
      trailingSlash = substr(path, -1) === '/';

  // Normalize the path
  path = normalizeArray(filter(path.split('/'), function(p) {
    return !!p;
  }), !isAbsolute).join('/');

  if (!path && !isAbsolute) {
    path = '.';
  }
  if (path && trailingSlash) {
    path += '/';
  }

  return (isAbsolute ? '/' : '') + path;
};

// posix version
exports.isAbsolute = function(path) {
  return path.charAt(0) === '/';
};

// posix version
exports.join = function() {
  var paths = Array.prototype.slice.call(arguments, 0);
  return exports.normalize(filter(paths, function(p, index) {
    if (typeof p !== 'string') {
      throw new TypeError('Arguments to path.join must be strings');
    }
    return p;
  }).join('/'));
};


// path.relative(from, to)
// posix version
exports.relative = function(from, to) {
  from = exports.resolve(from).substr(1);
  to = exports.resolve(to).substr(1);

  function trim(arr) {
    var start = 0;
    for (; start < arr.length; start++) {
      if (arr[start] !== '') break;
    }

    var end = arr.length - 1;
    for (; end >= 0; end--) {
      if (arr[end] !== '') break;
    }

    if (start > end) return [];
    return arr.slice(start, end - start + 1);
  }

  var fromParts = trim(from.split('/'));
  var toParts = trim(to.split('/'));

  var length = Math.min(fromParts.length, toParts.length);
  var samePartsLength = length;
  for (var i = 0; i < length; i++) {
    if (fromParts[i] !== toParts[i]) {
      samePartsLength = i;
      break;
    }
  }

  var outputParts = [];
  for (var i = samePartsLength; i < fromParts.length; i++) {
    outputParts.push('..');
  }

  outputParts = outputParts.concat(toParts.slice(samePartsLength));

  return outputParts.join('/');
};

exports.sep = '/';
exports.delimiter = ':';

exports.dirname = function(path) {
  var result = splitPath(path),
      root = result[0],
      dir = result[1];

  if (!root && !dir) {
    // No dirname whatsoever
    return '.';
  }

  if (dir) {
    // It has a dirname, strip trailing slash
    dir = dir.substr(0, dir.length - 1);
  }

  return root + dir;
};


exports.basename = function(path, ext) {
  var f = splitPath(path)[2];
  // TODO: make this comparison case-insensitive on windows?
  if (ext && f.substr(-1 * ext.length) === ext) {
    f = f.substr(0, f.length - ext.length);
  }
  return f;
};


exports.extname = function(path) {
  return splitPath(path)[3];
};

function filter (xs, f) {
    if (xs.filter) return xs.filter(f);
    var res = [];
    for (var i = 0; i < xs.length; i++) {
        if (f(xs[i], i, xs)) res.push(xs[i]);
    }
    return res;
}

// String.prototype.substr - negative index don't work in IE8
var substr = 'ab'.substr(-1) === 'b'
    ? function (str, start, len) { return str.substr(start, len) }
    : function (str, start, len) {
        if (start < 0) start = str.length + start;
        return str.substr(start, len);
    }
;

}).call(this,require('_process'))
},{"_process":134}],134:[function(require,module,exports){
// shim for using process in browser
var process = module.exports = {};

// cached from whatever global is present so that test runners that stub it
// don't break things.  But we need to wrap it in a try catch in case it is
// wrapped in strict mode code which doesn't define any globals.  It's inside a
// function because try/catches deoptimize in certain engines.

var cachedSetTimeout;
var cachedClearTimeout;

function defaultSetTimout() {
    throw new Error('setTimeout has not been defined');
}
function defaultClearTimeout () {
    throw new Error('clearTimeout has not been defined');
}
(function () {
    try {
        if (typeof setTimeout === 'function') {
            cachedSetTimeout = setTimeout;
        } else {
            cachedSetTimeout = defaultSetTimout;
        }
    } catch (e) {
        cachedSetTimeout = defaultSetTimout;
    }
    try {
        if (typeof clearTimeout === 'function') {
            cachedClearTimeout = clearTimeout;
        } else {
            cachedClearTimeout = defaultClearTimeout;
        }
    } catch (e) {
        cachedClearTimeout = defaultClearTimeout;
    }
} ())
function runTimeout(fun) {
    if (cachedSetTimeout === setTimeout) {
        //normal enviroments in sane situations
        return setTimeout(fun, 0);
    }
    // if setTimeout wasn't available but was latter defined
    if ((cachedSetTimeout === defaultSetTimout || !cachedSetTimeout) && setTimeout) {
        cachedSetTimeout = setTimeout;
        return setTimeout(fun, 0);
    }
    try {
        // when when somebody has screwed with setTimeout but no I.E. maddness
        return cachedSetTimeout(fun, 0);
    } catch(e){
        try {
            // When we are in I.E. but the script has been evaled so I.E. doesn't trust the global object when called normally
            return cachedSetTimeout.call(null, fun, 0);
        } catch(e){
            // same as above but when it's a version of I.E. that must have the global object for 'this', hopfully our context correct otherwise it will throw a global error
            return cachedSetTimeout.call(this, fun, 0);
        }
    }


}
function runClearTimeout(marker) {
    if (cachedClearTimeout === clearTimeout) {
        //normal enviroments in sane situations
        return clearTimeout(marker);
    }
    // if clearTimeout wasn't available but was latter defined
    if ((cachedClearTimeout === defaultClearTimeout || !cachedClearTimeout) && clearTimeout) {
        cachedClearTimeout = clearTimeout;
        return clearTimeout(marker);
    }
    try {
        // when when somebody has screwed with setTimeout but no I.E. maddness
        return cachedClearTimeout(marker);
    } catch (e){
        try {
            // When we are in I.E. but the script has been evaled so I.E. doesn't  trust the global object when called normally
            return cachedClearTimeout.call(null, marker);
        } catch (e){
            // same as above but when it's a version of I.E. that must have the global object for 'this', hopfully our context correct otherwise it will throw a global error.
            // Some versions of I.E. have different rules for clearTimeout vs setTimeout
            return cachedClearTimeout.call(this, marker);
        }
    }



}
var queue = [];
var draining = false;
var currentQueue;
var queueIndex = -1;

function cleanUpNextTick() {
    if (!draining || !currentQueue) {
        return;
    }
    draining = false;
    if (currentQueue.length) {
        queue = currentQueue.concat(queue);
    } else {
        queueIndex = -1;
    }
    if (queue.length) {
        drainQueue();
    }
}

function drainQueue() {
    if (draining) {
        return;
    }
    var timeout = runTimeout(cleanUpNextTick);
    draining = true;

    var len = queue.length;
    while(len) {
        currentQueue = queue;
        queue = [];
        while (++queueIndex < len) {
            if (currentQueue) {
                currentQueue[queueIndex].run();
            }
        }
        queueIndex = -1;
        len = queue.length;
    }
    currentQueue = null;
    draining = false;
    runClearTimeout(timeout);
}

process.nextTick = function (fun) {
    var args = new Array(arguments.length - 1);
    if (arguments.length > 1) {
        for (var i = 1; i < arguments.length; i++) {
            args[i - 1] = arguments[i];
        }
    }
    queue.push(new Item(fun, args));
    if (queue.length === 1 && !draining) {
        runTimeout(drainQueue);
    }
};

// v8 likes predictible objects
function Item(fun, array) {
    this.fun = fun;
    this.array = array;
}
Item.prototype.run = function () {
    this.fun.apply(null, this.array);
};
process.title = 'browser';
process.browser = true;
process.env = {};
process.argv = [];
process.version = ''; // empty string to avoid regexp issues
process.versions = {};

function noop() {}

process.on = noop;
process.addListener = noop;
process.once = noop;
process.off = noop;
process.removeListener = noop;
process.removeAllListeners = noop;
process.emit = noop;

process.binding = function (name) {
    throw new Error('process.binding is not supported');
};

process.cwd = function () { return '/' };
process.chdir = function (dir) {
    throw new Error('process.chdir is not supported');
};
process.umask = function() { return 0; };

},{}],135:[function(require,module,exports){
if (typeof Object.create === 'function') {
  // implementation from standard node.js 'util' module
  module.exports = function inherits(ctor, superCtor) {
    ctor.super_ = superCtor
    ctor.prototype = Object.create(superCtor.prototype, {
      constructor: {
        value: ctor,
        enumerable: false,
        writable: true,
        configurable: true
      }
    });
  };
} else {
  // old school shim for old browsers
  module.exports = function inherits(ctor, superCtor) {
    ctor.super_ = superCtor
    var TempCtor = function () {}
    TempCtor.prototype = superCtor.prototype
    ctor.prototype = new TempCtor()
    ctor.prototype.constructor = ctor
  }
}

},{}],136:[function(require,module,exports){
module.exports = function isBuffer(arg) {
  return arg && typeof arg === 'object'
    && typeof arg.copy === 'function'
    && typeof arg.fill === 'function'
    && typeof arg.readUInt8 === 'function';
}
},{}],137:[function(require,module,exports){
(function (process,global){
// Copyright Joyent, Inc. and other Node contributors.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.

var formatRegExp = /%[sdj%]/g;
exports.format = function(f) {
  if (!isString(f)) {
    var objects = [];
    for (var i = 0; i < arguments.length; i++) {
      objects.push(inspect(arguments[i]));
    }
    return objects.join(' ');
  }

  var i = 1;
  var args = arguments;
  var len = args.length;
  var str = String(f).replace(formatRegExp, function(x) {
    if (x === '%%') return '%';
    if (i >= len) return x;
    switch (x) {
      case '%s': return String(args[i++]);
      case '%d': return Number(args[i++]);
      case '%j':
        try {
          return JSON.stringify(args[i++]);
        } catch (_) {
          return '[Circular]';
        }
      default:
        return x;
    }
  });
  for (var x = args[i]; i < len; x = args[++i]) {
    if (isNull(x) || !isObject(x)) {
      str += ' ' + x;
    } else {
      str += ' ' + inspect(x);
    }
  }
  return str;
};


// Mark that a method should not be used.
// Returns a modified function which warns once by default.
// If --no-deprecation is set, then it is a no-op.
exports.deprecate = function(fn, msg) {
  // Allow for deprecating things in the process of starting up.
  if (isUndefined(global.process)) {
    return function() {
      return exports.deprecate(fn, msg).apply(this, arguments);
    };
  }

  if (process.noDeprecation === true) {
    return fn;
  }

  var warned = false;
  function deprecated() {
    if (!warned) {
      if (process.throwDeprecation) {
        throw new Error(msg);
      } else if (process.traceDeprecation) {
        console.trace(msg);
      } else {
        console.error(msg);
      }
      warned = true;
    }
    return fn.apply(this, arguments);
  }

  return deprecated;
};


var debugs = {};
var debugEnviron;
exports.debuglog = function(set) {
  if (isUndefined(debugEnviron))
    debugEnviron = process.env.NODE_DEBUG || '';
  set = set.toUpperCase();
  if (!debugs[set]) {
    if (new RegExp('\\b' + set + '\\b', 'i').test(debugEnviron)) {
      var pid = process.pid;
      debugs[set] = function() {
        var msg = exports.format.apply(exports, arguments);
        console.error('%s %d: %s', set, pid, msg);
      };
    } else {
      debugs[set] = function() {};
    }
  }
  return debugs[set];
};


/**
 * Echos the value of a value. Trys to print the value out
 * in the best way possible given the different types.
 *
 * @param {Object} obj The object to print out.
 * @param {Object} opts Optional options object that alters the output.
 */
/* legacy: obj, showHidden, depth, colors*/
function inspect(obj, opts) {
  // default options
  var ctx = {
    seen: [],
    stylize: stylizeNoColor
  };
  // legacy...
  if (arguments.length >= 3) ctx.depth = arguments[2];
  if (arguments.length >= 4) ctx.colors = arguments[3];
  if (isBoolean(opts)) {
    // legacy...
    ctx.showHidden = opts;
  } else if (opts) {
    // got an "options" object
    exports._extend(ctx, opts);
  }
  // set default options
  if (isUndefined(ctx.showHidden)) ctx.showHidden = false;
  if (isUndefined(ctx.depth)) ctx.depth = 2;
  if (isUndefined(ctx.colors)) ctx.colors = false;
  if (isUndefined(ctx.customInspect)) ctx.customInspect = true;
  if (ctx.colors) ctx.stylize = stylizeWithColor;
  return formatValue(ctx, obj, ctx.depth);
}
exports.inspect = inspect;


// http://en.wikipedia.org/wiki/ANSI_escape_code#graphics
inspect.colors = {
  'bold' : [1, 22],
  'italic' : [3, 23],
  'underline' : [4, 24],
  'inverse' : [7, 27],
  'white' : [37, 39],
  'grey' : [90, 39],
  'black' : [30, 39],
  'blue' : [34, 39],
  'cyan' : [36, 39],
  'green' : [32, 39],
  'magenta' : [35, 39],
  'red' : [31, 39],
  'yellow' : [33, 39]
};

// Don't use 'blue' not visible on cmd.exe
inspect.styles = {
  'special': 'cyan',
  'number': 'yellow',
  'boolean': 'yellow',
  'undefined': 'grey',
  'null': 'bold',
  'string': 'green',
  'date': 'magenta',
  // "name": intentionally not styling
  'regexp': 'red'
};


function stylizeWithColor(str, styleType) {
  var style = inspect.styles[styleType];

  if (style) {
    return '\u001b[' + inspect.colors[style][0] + 'm' + str +
           '\u001b[' + inspect.colors[style][1] + 'm';
  } else {
    return str;
  }
}


function stylizeNoColor(str, styleType) {
  return str;
}


function arrayToHash(array) {
  var hash = {};

  array.forEach(function(val, idx) {
    hash[val] = true;
  });

  return hash;
}


function formatValue(ctx, value, recurseTimes) {
  // Provide a hook for user-specified inspect functions.
  // Check that value is an object with an inspect function on it
  if (ctx.customInspect &&
      value &&
      isFunction(value.inspect) &&
      // Filter out the util module, it's inspect function is special
      value.inspect !== exports.inspect &&
      // Also filter out any prototype objects using the circular check.
      !(value.constructor && value.constructor.prototype === value)) {
    var ret = value.inspect(recurseTimes, ctx);
    if (!isString(ret)) {
      ret = formatValue(ctx, ret, recurseTimes);
    }
    return ret;
  }

  // Primitive types cannot have properties
  var primitive = formatPrimitive(ctx, value);
  if (primitive) {
    return primitive;
  }

  // Look up the keys of the object.
  var keys = Object.keys(value);
  var visibleKeys = arrayToHash(keys);

  if (ctx.showHidden) {
    keys = Object.getOwnPropertyNames(value);
  }

  // IE doesn't make error fields non-enumerable
  // http://msdn.microsoft.com/en-us/library/ie/dww52sbt(v=vs.94).aspx
  if (isError(value)
      && (keys.indexOf('message') >= 0 || keys.indexOf('description') >= 0)) {
    return formatError(value);
  }

  // Some type of object without properties can be shortcutted.
  if (keys.length === 0) {
    if (isFunction(value)) {
      var name = value.name ? ': ' + value.name : '';
      return ctx.stylize('[Function' + name + ']', 'special');
    }
    if (isRegExp(value)) {
      return ctx.stylize(RegExp.prototype.toString.call(value), 'regexp');
    }
    if (isDate(value)) {
      return ctx.stylize(Date.prototype.toString.call(value), 'date');
    }
    if (isError(value)) {
      return formatError(value);
    }
  }

  var base = '', array = false, braces = ['{', '}'];

  // Make Array say that they are Array
  if (isArray(value)) {
    array = true;
    braces = ['[', ']'];
  }

  // Make functions say that they are functions
  if (isFunction(value)) {
    var n = value.name ? ': ' + value.name : '';
    base = ' [Function' + n + ']';
  }

  // Make RegExps say that they are RegExps
  if (isRegExp(value)) {
    base = ' ' + RegExp.prototype.toString.call(value);
  }

  // Make dates with properties first say the date
  if (isDate(value)) {
    base = ' ' + Date.prototype.toUTCString.call(value);
  }

  // Make error with message first say the error
  if (isError(value)) {
    base = ' ' + formatError(value);
  }

  if (keys.length === 0 && (!array || value.length == 0)) {
    return braces[0] + base + braces[1];
  }

  if (recurseTimes < 0) {
    if (isRegExp(value)) {
      return ctx.stylize(RegExp.prototype.toString.call(value), 'regexp');
    } else {
      return ctx.stylize('[Object]', 'special');
    }
  }

  ctx.seen.push(value);

  var output;
  if (array) {
    output = formatArray(ctx, value, recurseTimes, visibleKeys, keys);
  } else {
    output = keys.map(function(key) {
      return formatProperty(ctx, value, recurseTimes, visibleKeys, key, array);
    });
  }

  ctx.seen.pop();

  return reduceToSingleString(output, base, braces);
}


function formatPrimitive(ctx, value) {
  if (isUndefined(value))
    return ctx.stylize('undefined', 'undefined');
  if (isString(value)) {
    var simple = '\'' + JSON.stringify(value).replace(/^"|"$/g, '')
                                             .replace(/'/g, "\\'")
                                             .replace(/\\"/g, '"') + '\'';
    return ctx.stylize(simple, 'string');
  }
  if (isNumber(value))
    return ctx.stylize('' + value, 'number');
  if (isBoolean(value))
    return ctx.stylize('' + value, 'boolean');
  // For some reason typeof null is "object", so special case here.
  if (isNull(value))
    return ctx.stylize('null', 'null');
}


function formatError(value) {
  return '[' + Error.prototype.toString.call(value) + ']';
}


function formatArray(ctx, value, recurseTimes, visibleKeys, keys) {
  var output = [];
  for (var i = 0, l = value.length; i < l; ++i) {
    if (hasOwnProperty(value, String(i))) {
      output.push(formatProperty(ctx, value, recurseTimes, visibleKeys,
          String(i), true));
    } else {
      output.push('');
    }
  }
  keys.forEach(function(key) {
    if (!key.match(/^\d+$/)) {
      output.push(formatProperty(ctx, value, recurseTimes, visibleKeys,
          key, true));
    }
  });
  return output;
}


function formatProperty(ctx, value, recurseTimes, visibleKeys, key, array) {
  var name, str, desc;
  desc = Object.getOwnPropertyDescriptor(value, key) || { value: value[key] };
  if (desc.get) {
    if (desc.set) {
      str = ctx.stylize('[Getter/Setter]', 'special');
    } else {
      str = ctx.stylize('[Getter]', 'special');
    }
  } else {
    if (desc.set) {
      str = ctx.stylize('[Setter]', 'special');
    }
  }
  if (!hasOwnProperty(visibleKeys, key)) {
    name = '[' + key + ']';
  }
  if (!str) {
    if (ctx.seen.indexOf(desc.value) < 0) {
      if (isNull(recurseTimes)) {
        str = formatValue(ctx, desc.value, null);
      } else {
        str = formatValue(ctx, desc.value, recurseTimes - 1);
      }
      if (str.indexOf('\n') > -1) {
        if (array) {
          str = str.split('\n').map(function(line) {
            return '  ' + line;
          }).join('\n').substr(2);
        } else {
          str = '\n' + str.split('\n').map(function(line) {
            return '   ' + line;
          }).join('\n');
        }
      }
    } else {
      str = ctx.stylize('[Circular]', 'special');
    }
  }
  if (isUndefined(name)) {
    if (array && key.match(/^\d+$/)) {
      return str;
    }
    name = JSON.stringify('' + key);
    if (name.match(/^"([a-zA-Z_][a-zA-Z_0-9]*)"$/)) {
      name = name.substr(1, name.length - 2);
      name = ctx.stylize(name, 'name');
    } else {
      name = name.replace(/'/g, "\\'")
                 .replace(/\\"/g, '"')
                 .replace(/(^"|"$)/g, "'");
      name = ctx.stylize(name, 'string');
    }
  }

  return name + ': ' + str;
}


function reduceToSingleString(output, base, braces) {
  var numLinesEst = 0;
  var length = output.reduce(function(prev, cur) {
    numLinesEst++;
    if (cur.indexOf('\n') >= 0) numLinesEst++;
    return prev + cur.replace(/\u001b\[\d\d?m/g, '').length + 1;
  }, 0);

  if (length > 60) {
    return braces[0] +
           (base === '' ? '' : base + '\n ') +
           ' ' +
           output.join(',\n  ') +
           ' ' +
           braces[1];
  }

  return braces[0] + base + ' ' + output.join(', ') + ' ' + braces[1];
}


// NOTE: These type checking functions intentionally don't use `instanceof`
// because it is fragile and can be easily faked with `Object.create()`.
function isArray(ar) {
  return Array.isArray(ar);
}
exports.isArray = isArray;

function isBoolean(arg) {
  return typeof arg === 'boolean';
}
exports.isBoolean = isBoolean;

function isNull(arg) {
  return arg === null;
}
exports.isNull = isNull;

function isNullOrUndefined(arg) {
  return arg == null;
}
exports.isNullOrUndefined = isNullOrUndefined;

function isNumber(arg) {
  return typeof arg === 'number';
}
exports.isNumber = isNumber;

function isString(arg) {
  return typeof arg === 'string';
}
exports.isString = isString;

function isSymbol(arg) {
  return typeof arg === 'symbol';
}
exports.isSymbol = isSymbol;

function isUndefined(arg) {
  return arg === void 0;
}
exports.isUndefined = isUndefined;

function isRegExp(re) {
  return isObject(re) && objectToString(re) === '[object RegExp]';
}
exports.isRegExp = isRegExp;

function isObject(arg) {
  return typeof arg === 'object' && arg !== null;
}
exports.isObject = isObject;

function isDate(d) {
  return isObject(d) && objectToString(d) === '[object Date]';
}
exports.isDate = isDate;

function isError(e) {
  return isObject(e) &&
      (objectToString(e) === '[object Error]' || e instanceof Error);
}
exports.isError = isError;

function isFunction(arg) {
  return typeof arg === 'function';
}
exports.isFunction = isFunction;

function isPrimitive(arg) {
  return arg === null ||
         typeof arg === 'boolean' ||
         typeof arg === 'number' ||
         typeof arg === 'string' ||
         typeof arg === 'symbol' ||  // ES6 symbol
         typeof arg === 'undefined';
}
exports.isPrimitive = isPrimitive;

exports.isBuffer = require('./support/isBuffer');

function objectToString(o) {
  return Object.prototype.toString.call(o);
}


function pad(n) {
  return n < 10 ? '0' + n.toString(10) : n.toString(10);
}


var months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep',
              'Oct', 'Nov', 'Dec'];

// 26 Feb 16:19:34
function timestamp() {
  var d = new Date();
  var time = [pad(d.getHours()),
              pad(d.getMinutes()),
              pad(d.getSeconds())].join(':');
  return [d.getDate(), months[d.getMonth()], time].join(' ');
}


// log is just a thin wrapper to console.log that prepends a timestamp
exports.log = function() {
  console.log('%s - %s', timestamp(), exports.format.apply(exports, arguments));
};


/**
 * Inherit the prototype methods from one constructor into another.
 *
 * The Function.prototype.inherits from lang.js rewritten as a standalone
 * function (not on Function.prototype). NOTE: If this file is to be loaded
 * during bootstrapping this function needs to be rewritten using some native
 * functions as prototype setup using normal JavaScript does not work as
 * expected during bootstrapping (see mirror.js in r114903).
 *
 * @param {function} ctor Constructor function which needs to inherit the
 *     prototype.
 * @param {function} superCtor Constructor function to inherit prototype from.
 */
exports.inherits = require('inherits');

exports._extend = function(origin, add) {
  // Don't do anything if add isn't an object
  if (!add || !isObject(add)) return origin;

  var keys = Object.keys(add);
  var i = keys.length;
  while (i--) {
    origin[keys[i]] = add[keys[i]];
  }
  return origin;
};

function hasOwnProperty(obj, prop) {
  return Object.prototype.hasOwnProperty.call(obj, prop);
}

}).call(this,require('_process'),typeof global !== "undefined" ? global : typeof self !== "undefined" ? self : typeof window !== "undefined" ? window : {})
},{"./support/isBuffer":136,"_process":134,"inherits":135}],138:[function(require,module,exports){
// samples.js, generated from genfiles.sh
var files = {};
files['repl.lithp'] = require('./lithp/repl.lithp');
files['macro-test.lithp'] = require('./lithp/macro-test.lithp');
files['modules/pivot.lithp'] = require('./lithp/modules/pivot.lithp');
files['modules/cache.lithp'] = require('./lithp/modules/cache.lithp');
files['modules/repl.lithp'] = require('./lithp/modules/repl.lithp');
files['modules/file.lithp'] = require('./lithp/modules/file.lithp');
files['modules/switch.lithp'] = require('./lithp/modules/switch.lithp');
files['modules/bignum.lithp'] = require('./lithp/modules/bignum.lithp');
files['modules/match.lithp'] = require('./lithp/modules/match.lithp');
files['modules/assert.lithp'] = require('./lithp/modules/assert.lithp');
files['modules/stderr.lithp'] = require('./lithp/modules/stderr.lithp');
files['modules/stream.lithp'] = require('./lithp/modules/stream.lithp');
files['modules/strings.lithp'] = require('./lithp/modules/strings.lithp');
files['modules/readline.lithp'] = require('./lithp/modules/readline.lithp');
files['modules/math.lithp'] = require('./lithp/modules/math.lithp');
files['modules/buffer.lithp'] = require('./lithp/modules/buffer.lithp');
files['modules/stdlib.lithp'] = require('./lithp/modules/stdlib.lithp');
files['modules/random.lithp'] = require('./lithp/modules/random.lithp');
files['modules/class.lithp'] = require('./lithp/modules/class.lithp');
files['modules/lists.lithp'] = require('./lithp/modules/lists.lithp');
files['modules/symbols.lithp'] = require('./lithp/modules/symbols.lithp');
files['macro.lithp'] = require('./lithp/macro.lithp');
files['samples/fndefs.lithp'] = require('./lithp/samples/fndefs.lithp');
files['samples/module.lithp'] = require('./lithp/samples/module.lithp');
files['samples/var_args.lithp'] = require('./lithp/samples/var_args.lithp');
files['samples/interlace-strings.lithp'] = require('./lithp/samples/interlace-strings.lithp');
files['samples/readfile.lithp'] = require('./lithp/samples/readfile.lithp');
files['samples/bfib.lithp'] = require('./lithp/samples/bfib.lithp');
files['samples/progruzzle-colf.lithp'] = require('./lithp/samples/progruzzle-colf.lithp');
files['samples/inverse.lithp'] = require('./lithp/samples/inverse.lithp');
files['samples/recurse.lithp'] = require('./lithp/samples/recurse.lithp');
files['samples/pow.lithp'] = require('./lithp/samples/pow.lithp');
files['samples/pillow.lithp'] = require('./lithp/samples/pillow.lithp');
files['samples/module_lib.lithp'] = require('./lithp/samples/module_lib.lithp');
files['samples/calc.lithp'] = require('./lithp/samples/calc.lithp');
files['samples/one_to_ten.lithp'] = require('./lithp/samples/one_to_ten.lithp');
files['samples/integral.lithp'] = require('./lithp/samples/integral.lithp');
files['samples/subchains.lithp'] = require('./lithp/samples/subchains.lithp');
files['samples/factorial.lithp'] = require('./lithp/samples/factorial.lithp');
files['samples/wall.lithp'] = require('./lithp/samples/wall.lithp');
files['samples/fib.lithp'] = require('./lithp/samples/fib.lithp');
files['samples/n-circles.lithp'] = require('./lithp/samples/n-circles.lithp');
files['samples/scope.lithp'] = require('./lithp/samples/scope.lithp');
files['samples/simple.lithp'] = require('./lithp/samples/simple.lithp');
files['samples/while.lithp'] = require('./lithp/samples/while.lithp');
files['samples/ext.lithp'] = require('./lithp/samples/ext.lithp');
files['samples/definitions.lithp'] = require('./lithp/samples/definitions.lithp');
files['samples/oddword.lithp'] = require('./lithp/samples/oddword.lithp');
files['samples/shorthand.lithp'] = require('./lithp/samples/shorthand.lithp');
files['samples/square.lithp'] = require('./lithp/samples/square.lithp');
files['samples/eval.lithp'] = require('./lithp/samples/eval.lithp');
files['samples/aspect.lithp'] = require('./lithp/samples/aspect.lithp');
files['samples/atoms.lithp'] = require('./lithp/samples/atoms.lithp');
files['samples/forloop.lithp'] = require('./lithp/samples/forloop.lithp');
files['samples/complex.lithp'] = require('./lithp/samples/complex.lithp');
files['samples/md-template.lithp'] = require('./lithp/samples/md-template.lithp');
files['samples/map.lithp'] = require('./lithp/samples/map.lithp');
files['samples/pairable.lithp'] = require('./lithp/samples/pairable.lithp');
files['modules/jquery-toolkit.lithp'] = require('./modules/./jquery-toolkit.lithp');
files['modules/html.lithp'] = require('./modules/./html.lithp');
files['modules/html-toolkit.lithp'] = require('./modules/./html-toolkit.lithp');
files['webide/webide.lithp'] = require('./webide/./webide.lithp');
files['webide/palette.lithp'] = require('./webide/./palette.lithp');
module.exports = files;


},{"./lithp/macro-test.lithp":16,"./lithp/macro.lithp":17,"./lithp/modules/assert.lithp":19,"./lithp/modules/bignum.lithp":21,"./lithp/modules/buffer.lithp":23,"./lithp/modules/cache.lithp":25,"./lithp/modules/class.lithp":27,"./lithp/modules/file.lithp":29,"./lithp/modules/lists.lithp":31,"./lithp/modules/match.lithp":33,"./lithp/modules/math.lithp":35,"./lithp/modules/pivot.lithp":37,"./lithp/modules/random.lithp":39,"./lithp/modules/readline.lithp":41,"./lithp/modules/repl.lithp":43,"./lithp/modules/stderr.lithp":45,"./lithp/modules/stdlib.lithp":47,"./lithp/modules/stream.lithp":49,"./lithp/modules/strings.lithp":51,"./lithp/modules/switch.lithp":53,"./lithp/modules/symbols.lithp":55,"./lithp/repl.lithp":60,"./lithp/samples/aspect.lithp":62,"./lithp/samples/atoms.lithp":64,"./lithp/samples/bfib.lithp":66,"./lithp/samples/calc.lithp":68,"./lithp/samples/complex.lithp":70,"./lithp/samples/definitions.lithp":72,"./lithp/samples/eval.lithp":74,"./lithp/samples/ext.lithp":76,"./lithp/samples/factorial.lithp":78,"./lithp/samples/fib.lithp":80,"./lithp/samples/fndefs.lithp":82,"./lithp/samples/forloop.lithp":84,"./lithp/samples/integral.lithp":86,"./lithp/samples/interlace-strings.lithp":88,"./lithp/samples/inverse.lithp":90,"./lithp/samples/map.lithp":92,"./lithp/samples/md-template.lithp":94,"./lithp/samples/module.lithp":96,"./lithp/samples/module_lib.lithp":98,"./lithp/samples/n-circles.lithp":100,"./lithp/samples/oddword.lithp":102,"./lithp/samples/one_to_ten.lithp":104,"./lithp/samples/pairable.lithp":106,"./lithp/samples/pillow.lithp":108,"./lithp/samples/pow.lithp":110,"./lithp/samples/progruzzle-colf.lithp":112,"./lithp/samples/readfile.lithp":114,"./lithp/samples/recurse.lithp":116,"./lithp/samples/scope.lithp":118,"./lithp/samples/shorthand.lithp":120,"./lithp/samples/simple.lithp":122,"./lithp/samples/square.lithp":124,"./lithp/samples/subchains.lithp":126,"./lithp/samples/var_args.lithp":128,"./lithp/samples/wall.lithp":130,"./lithp/samples/while.lithp":132,"./modules/./html-toolkit.lithp":4,"./modules/./html.lithp":6,"./modules/./jquery-toolkit.lithp":8,"./webide/./palette.lithp":140,"./webide/./webide.lithp":142}],139:[function(require,module,exports){
module.exports=[[["import","html-toolkit"],["import","jquery-toolkit"],["def","msgEditorStateKeybindings",{"code":[[["\"msgEditorStateKeybindings\""]]],"_fndef":true,"_fnparams":[]}],["def","msgSetEditorState",{"code":[[["dict",["tuple","type","\"msgSetEditorState\""],["tuple","stateName","StateName"],["tuple","stateValue","StateValue"]]]],"_fndef":true,"_fnparams":["StateName","StateValue"]}],["export-global","msgSetEditorState/2","msgEditorStateKeybindings/0"],["jqueryOnLoad",{"code":[[["print","\"Palette: registering behaviours\""],["var","WidgetKeybinding",["jQuery","\"select#keybinding\""]],["member-call","WidgetKeybinding","bind","\"change\"",["scope",{"code":[[["var","Value",["member-call","WidgetKeybinding","getValue"]],["postParentMessage",["msgSetEditorState",["msgEditorStateKeybindings"],"Value"]]]],"_fndef":true,"_fnparams":[]}]]]],"_fndef":true,"_fnparams":[]}]]]
},{}],140:[function(require,module,exports){
module.exports = "% Web IDE 2 module: Palette\n%\n% Handles the editor palette sidebar.\n%\n(\n\t(import html-toolkit)\n\t(import jquery-toolkit)\n\n\t% These structures are the same as in ../html/types.js\n\t(def msgEditorStateKeybindings # :: ((\"msgEditorStateKeybindings\")))\n\t(def msgSetEditorState #StateName,StateValue :: (\n\t\t(dict\n\t\t\t(tuple type \"msgSetEditorState\")\n\t\t\t(tuple stateName StateName)\n\t\t\t(tuple stateValue StateValue)\n\t\t)\n\t))\n\t(export-global msgSetEditorState/2 msgEditorStateKeybindings/0)\n\n\t% $(function () {\n\t(jqueryOnLoad # :: (\n\t\t(print \"Palette: registering behaviours\")\n\t\t% Grab the keybinding element by id (looks just like jQuery in Javascript!)\n\t\t(var WidgetKeybinding (jQuery \"select#keybinding\"))\n\t\t% Assign a handler to the \"change\" event. Essentially, WidgetKeybinding.bind(\"change\", function() { ... })\n\t\t(member-call WidgetKeybinding bind \"change\" (scope # :: (\n\t\t\t% Get the value of the widget, ie WidgetKeybinding.val()\n\t\t\t% Note that the jQuery interface in Lithp provides getValue() and setValue() instead of val(...)\n\t\t\t(var Value (member-call WidgetKeybinding getValue))\n\t\t\t% Provided by HTML-toolkit, allows passing a message to the parent frame, index.html.\n\t\t\t(postParentMessage (msgSetEditorState (msgEditorStateKeybindings) Value))\n\t\t)))\n\t))\n\t% }\n)\n";

},{}],141:[function(require,module,exports){
module.exports=[[["import","class"]]]
},{}],142:[function(require,module,exports){
module.exports = "% Provides an interface to the WebIDE document.\n(\n\t(import class)\n%\t(import \"html-toolkit\")\n%\t(import \"jquery-toolkit\")\n%\n%\t(jqueryOnLoad (scope # :: (\n%\t\t(print \"Secondary jQuery init\")\n%\t\t(var Body (jQuery \"body\"))\n%\t\t(print \"Body: \" Body)\n%\t\t(var Anchors (jQuery \"a\" Body))\n%\t\t(print \"Anchors:\" Anchors)\n%\t\t(member-call Anchors setCss (dict (tuple color \"red\")))\n%\t\t(var B (jQuery \"<b>TEST</b>\"))\n%\t\t(member-call Body append B)\n%\t)))\n)\n";

},{}]},{},[2,138]);
