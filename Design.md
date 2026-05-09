# Component Overview
Access each component through an interface.

## Object
Contains data about a object and its metadata.
Methods:
- Get object metadata
Metadata:
- Name
- uid

### Directory Object
Methods:
- Get parent
- Get directory listing
Data:
- List of all objects located under the directory
- Parent directory

### File Object
Methods:
- Get object data
Metadata:
- file size in bytes
- file type

## ACL
Contains a list of the access control that should be enforced for each file

## SFS - Secure File System
    - Stores all the files and directories, including the metadata
    - Encrypts the data using keys from the KS
    - Interface methods:
        - Get object metadata
        - Get object
        - Write to object
        - Create object
## UAH - User Access Handler
    - Middleware between the user and the SFS.
    - Uses the AH to check for authorization
    - Secured using the STM
    - Interface methods:
        - Read file
        - Read directory
        - Write to file
        - Create directory
        - Create file

## AH - Authorization Handler
    - Checks for authorization and authenticates users
    - Interface methods:
        - Authenticate user
        - User Authorization
        - Create user
        - Add user privileges
        - Revoke user privileges
        - Delete user
## KS - Key Store
    - Stores the symmetric keys used by the SFS
    - Secured using the STM
    - Interface methods: (can only be run from the SFS or other authorized components)
        - Encrypt object
        - Decrypt object
## CS - Credential Store
    - Stores all the credentials for all users, including their public key and needed identification to authenticate them
    - Secured using the STM
    - Interface methods: (Can only be called from the AH, unless otherwise noted)
        - Encrypt object using users public key
        - Get user identifiable information
        - Create user credentials
        - Modify user
        - Delete user
## STM - Secure Storage Mechanism (Trusted Computing)
    - Uses TPM or other similar mechanisms to securely store and handle all the encryption

## UI
- Download files
- View files
- Upload files
- Edit files?


# Usage steps, Algorithm
- Every action is checked for authorization.

1. User authenticates through the UAH
2. The UAH returns a directory listing of all accessible files and directories the user is authorized for.
    - Each security domain is individually checked, only directly visible directories and files should be returned.
3. User chooses a file or directory to access
4. Authorization is checked if access is allowed
5. File or directory listing is returned
6. Return to step 3
