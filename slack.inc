<?php
/*
 * Enterprise - Ultra Simple Slack Entergration
 *
 * slack.inc - Basic input and output hooks for Slack
 *
 * Version 1.0
 *
 *  AUTHOR: Steven Goodwin (StevenGoodwin@gmail.com)
 *			Copyright 2016, Steven Goodwin.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016, Steven Goodwin.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


class SlackMessage {
public $text;
public $channel;
public $username;
public $emoji;

	public function __construct($data) {
		$this->text = @$data['text'] ?: "";
		if (isset($data['trigger_word'])) {
			$this->text = substr($this->text, strlen($data['trigger_word'])+1);
		}

		$this->channel = @$data['channel_name'] ?: "#announcements";
		$this->emoji = ":ghost:";
		$this->username = "Botty McBotface";

		$this->handle = function($msg) { 
			print $msg->getReply(); 
		};
	}

	public function getReply() {
        return json_encode(array(
                "channel"       => $this->channel,
                "username"      => $this->username,
                "text"          => $this->text,
                "icon_emoji"    => $this->emoji
		));
	}

	public function setOutgoingHandler($handle) {
		$this->handle = $handle;
		return $this;
	}

	public function setReplyText($text) {
		$this->text = $text;
		return $this;
	}

	public function setChannel($channel) {
		$this->channel = $channel;
		return $this;
	}

	public function setUsername($name) {
		$this->username = $name;
		return $this;
	}

	public function setUserID($id) {
		$this->userid = $id;
		return $this;
	}

	public function setEmoji($emoji) {
		$this->emoji = $emoji;
		return $this;
	}

	public function send() {
		return call_user_func($this->handle, $this);
	}

};

class SlackConduitIn {
	public function __construct($token) {
		$this->token = $token;
	}

	public function onReceive($data) {
		if ($this->token == $data['token']) {
			$msg = new SlackMessage($data);
			$msg->setUsername($data['user_name']);
			$msg->setUserID($data['user_id']);
			return $msg;
		}
		return NULL;
	}
}


class SlackConduitOut {

	public function __construct($hook) {
		$this->hook = $hook;
	}

	public function createMessage($message) {
		$msg = new SlackMessage(array('text' => $message));
		$msg->setOutgoingHandler(function($msg) {
	        $data = "payload=" . $msg->getReply();

        	$ch = curl_init($this->hook);
        	curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
        	curl_setopt($ch, CURLOPT_POSTFIELDS, $data);
        	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        	$result = curl_exec($ch);
        	curl_close($ch);
	
        	return $result;
		});
		return $msg;
	}
};

?>
