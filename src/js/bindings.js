//BEGIN SETUP
            function output(message)
            {
                var output = document.getElementById("output");
                output.innerHTML = output.innerHTML + message + "\n";
            }
window.onload = function() {
 	new QWebChannel(qt.webChannelTransport, function(channel) {
    // all published objects are available in channel.objects under
    // the identifier set in their attached WebChannel.id property
    console.log("getting Foo");
    window.foo = channel.objects.foo;
    window.foo.showNotification("Yolo!", "Bla");
    console.log("tried to print");
});
}
