var a=1;
var b=1;
var c=a+b;
nativeLoggingHook('nativeLoggingHook', 1);
__myfunctionSync = function(args){
    nativeLoggingHook('__myfunctionSync,args1:' + args[0] + ",arg2:" +args[1], 1);
    return {key1:'value1', key2:'value2'}
}
__myfunction = function(args, callback){
    nativeLoggingHook('__myfunction', 1);
    callback({key11:'callback-1', key22:"value2"});
}