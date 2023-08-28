const acceptedMimes = new Set(["image/jpeg", "image/png", "image/gif", "image/svg+xml", "image/tiff", "image/webp"])

// This is the name of the key specified within the nativemessaginghost registry
// The creation of this key is found within ImageSourcerHost/create_reg.cpp
let port = chrome.runtime.connectNative('com.toothbrush.imsrc');

port.onMessage.addListener(function (msg) {
	if(chrome.runtime.lastError) {
		console.log(chrome.runtime.lastError)
		return
	}
	console.log('Received' + msg);
});

port.onDisconnect.addListener(function () {
	console.log('Disconnected');
});

chrome.downloads.onCreated.addListener((dlItem) => {
	if(dlItem.state !== "in_progress" || !acceptedMimes.has(dlItem.mime)) {
		return
	}
	try {
		console.log("here", dlItem.finalUrl, dlItem.url, dlItem.mime)
		port.postMessage({text: dlItem.url});
// 		chrome.runtime.sendNativeMessage(
// 		  'com.toothbrush.imsrc',
// 		  {text: dlItem.url},
// 		  function (response) {
// 			console.log(response)
// 			console.log('Received ' + response);
// 		  }
// 		);
	} catch {
		console.log(chrome.runtime.lastError)
	}
})

chrome.downloads.onChanged.addListener((dlDelta) => {
	chrome.downloads.search({id: dlDelta.id}, (dlItems) => {
		console.log(dlItems)
		let dlItem = dlItems[0]
		if(!acceptedMimes.has(dlItem.mime)) {
			return
		}
		if(dlItem.state === "complete") {
			console.log("completed DL", dlItem.filename)
		}
	})
})
