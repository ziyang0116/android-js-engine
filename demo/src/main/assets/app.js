(function(global){
    nativeLoggingHook('js-engine', 1);
    global.myfunctionSync = function(args){
        nativeLoggingHook('myfunctionSync,args1:' + args[0] + ",arg2:" +args[1], 1);
        return {key1:'value1', key2:'value2'}
    }
    global.myfunction = function(args, callback){
        nativeLoggingHook('myfunction', 1);
        callback({key11:'callback-1', key22:"value2"});
    }
})(this);