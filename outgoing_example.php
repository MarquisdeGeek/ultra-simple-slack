<?php

require 'slack.inc';

$token = "YOUR_TOKEN_GOES_HERE";

$slack = new SlackConduitIn($token);

$msg = $slack->onReceive($_POST);

if ($msg) {
	$reply="You said " . $msg->text;
	$msg->setReplyText($reply)->setUsername("ReplyBot")->send();
} else {
	error_log("I don't think that token was correct. Someone other than Slack is using this URL!");
}

?>