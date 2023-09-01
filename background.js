const acceptedMimes = new Set(["image/jpeg", "image/png", "image/gif", "image/svg+xml", "image/tiff", "image/webp"])

// This is the name of the key specified within the nativemessaginghost registry
// The creation of this key is found within ImageSourcerHost/create_reg.cpp
let port = chrome.runtime.connectNative('com.toothbrush.imsrc');

port.onMessage.addListener(function (msg) {
	if(chrome.runtime.lastError) {
		console.log(chrome.runtime.lastError)
		return
	}
	console.log('Received Response:');
	console.log(msg)
});

port.onDisconnect.addListener(function () {
	console.log('Disconnected');
});

chrome.downloads.onCreated.addListener((dlItem) => {
	if(dlItem.state !== "in_progress" || !acceptedMimes.has(dlItem.mime)) {
		return
	}
	console.log("DLItem Created:", dlItem.finalUrl, dlItem.url, dlItem.mime)
})

chrome.downloads.onChanged.addListener((dlDelta) => {
	chrome.downloads.search({id: dlDelta.id}, (dlItems) => {
		let dlItem = dlItems[0]
		if(!dlItem.exists || dlItem.state !== "complete" || !acceptedMimes.has(dlItem.mime)) {
			return
		}
		console.log(dlItems)
		console.log("Completed DL", dlItem.filename)
		port.postMessage({
			hostUrl: dlItem.referrer,
			imgUrl: dlItem.url,
			imgFilepath: dlItem.filename
		});
	})
})
