# ultra-simple-slack
USS Enterprise - Ultra Simple Slack Entergration

## About

This library lets your post, and respond to, messages from your Slack channel. It uses no plug-ins, libraries, or
extra cruft (except for curl.)


## Requirements and installation

* PHP5+
* Curl
* A Slack account


You can install this through your package manager. e.g

```
apt-get install php5 php5-curl
```


## Incoming Messages
### (Or, How to post messages, at any time, INto a Slack channel)

This requires you to set-up and configure an incoming webhook. See

https://api.slack.com/incoming-webhooks

for details on how to set-up a new one. (Currently this directs to your_slack.slack.com/services) This should result in a URL which looks like,

https://hooks.slack.com/services/T702JHADW/37B2JHKMF/9mmWchB3BPnc0IbkNlmlMIXY

Write this into the line

```
$token = "https://hooks.slack.com/services/T702JHADW/37B2JHKMF/9mmWchB3BPnc0IbkNlmlMIXY";

```

And test with

```
php incoming_example.php
```


## Outgoing Messages 
### (or, How to listen for, and respond to, text coming OUT of a Slack channel)

This requires you to set-up and configure an outgoing webhook. See

https://api.slack.com/outgoing-webhooks

for details. You must set up a trigger word, which is the one which prefixes all commands. When Slack sees a
sentance beginning with this word, it calls a URL on your server, with details of the message. This URL must be
accessible from a remote server, so if you have a username/password on your server you must either

1. Include it in the URL, e.g. http://username:password@my.domain.name
2. Set-up a separate service, such as one on port 81

I use the latter,

```
http://my.domain.name:81/slack/out.php
```

Copy the token from the Slack services page. It will look similar to jm9o6aozp0xPh0xLxz7rG1pG and add this to the code,

```
$token = "jm9o6aozp0xPh0xLxz7rG1pG";

```

To test this, go to the slack and type the trigger word, followed by some text.




