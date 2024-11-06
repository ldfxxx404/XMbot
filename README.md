# XMbot Documentation

## Overview

XMbot is a lightweight XMPP bot designed with minimal functionality to support basic messaging operations over the XMPP protocol.

## Requirements

gloox - lib for xmmp bot
python3 - scripts

## Installation
Install python req file 
```bash
pip install -r requirements.txt
```
To build and run XMbot, use the provided installation script. Follow the instructions below to set up the environment and configure the bot.

### Prerequisites

1. **Ensure required packages**:
   - Install any dependencies specified in `install.sh` (for example, `xmpppy` or `sleekxmpp`, if required).
   - Docker (if using Docker for deployment).

2. **Configuration**:
   - Create a `.env` file in the root directory of the project.
   - Add the following environment variables in `.env`:

     ```bash
      USERNAME=login.xmpp
      PASSWORD=password

     ```

## Building the Bot

### Using the Installation Script

1. Clone the repository:

   ```bash
   git clone <repository-url>
   cd XMbot
   ```

2. Run the installation script:

   ```bash
   ./install.sh
   ```

This script will install all necessary dependencies and prepare the bot for execution.

### Using Docker

If you prefer to use Docker:

1. **Build the Docker Image**:

   ```bash
   sudo docker build -t <bot_name> .
   ```

2. **Run the Docker Container**:

   ```bash
   sudo docker run <bot_name>
   ```

## Environment Configuration

In the `.env` file, define the following credentials and settings for the bot to connect to the XMPP server:

```bash
USERNAME=bot.xmpp
PASSWORD=password
```

### Important Environment Variables

- `USERNAME`: The bot’s XMPP username.
- `PASSWORD`: The password associated with the XMPP account.

## Usage

Once the setup is complete, you can start the bot using the Docker container or by running it directly, if you’ve used the install script.

1. **Starting the Bot Locally**:
   
   ```bash
   cd build
   ./XMbot
   ```

2. **Starting the Bot in Docker**:

   ```bash
   sudo docker run <bot_name>
   ```

After launching, the bot will connect to the XMPP server using the provided credentials and start interacting as per the predefined functionality.

## Extending the Bot

The XMbot is designed for minimal functionality but can be extended for various XMPP operations:

- **Message Handling**: Customize message responses by modifying the handler functions in the main script.
- **Room Management**: Implement multi-user chat features if needed.
- **Custom Commands**: Add support for custom commands by defining patterns and responses.

## Troubleshooting

- **Connection Issues**: Ensure the correct credentials and server address are specified in `.env`.
- **Missing Dependencies**: Rerun `./install.sh` to check dependencies.
- **Environment Variables**: Confirm that all required environment variables are set in `.env`.

