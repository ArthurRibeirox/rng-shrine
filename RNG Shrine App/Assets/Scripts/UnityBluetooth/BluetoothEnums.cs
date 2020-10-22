namespace UnityBluetooth
{
    public enum BluetoothBondState
    {
        None = 10,
        Bonding = 11,
        Bonded = 12,
    }

    public enum BluetoothDeviceType
    {
        Misc = 0x0000,
        Computer = 0x0100,
        Phone = 0x0200,
        Networking = 0x0300,
        AudioVideo = 0x0400,
        Peripheral = 0x0500,
        Imaging = 0x0600,
        Wearable = 0x0700,
        Toy = 0x0800,
        Health = 0x0900,
        Uncategorized = 0x1F00,
    }

    public enum BluetoothDeviceSubType {
        // COMPUTER subType
        ComputerUncategorized = 0x0100,
        ComputerDesktop = 0x0104,
        ComputerServer = 0x0108,
        ComputerLaptop = 0x010C,
        ComputerHandheldPcPda = 0x0110,
        ComputerPalmSizePcPda = 0x0114,
        ComputerWearable = 0x0118,

        // PHONE subType
        PhoneUncategorized = 0x0200,
        PhoneCellular = 0x0204,
        PhoneCordless = 0x0208,
        PhoneSmart = 0x020C,
        PhoneModemOrGateway = 0x0210,
        PhoneIsdn = 0x0214,

        // AUDIO_VIDEO subType
        AudioVideoUncategorized = 0x0400,
        AudioVideoWearableHeadset = 0x0404,
        AudioVideoHandsfree = 0x0408,
        AudioVideoMicrophone = 0x0410,
        AudioVideoLoudspeaker = 0x0414,
        AudioVideoHeadphones = 0x0418,
        AudioVideoPortableAudio = 0x041C,
        AudioVideoCarAudio = 0x0420,
        AudioVideoSetTopBox = 0x0424,
        AudioVideoHifiAudio = 0x0428,
        AudioVideoVcr = 0x042C,
        AudioVideoVideoCamera = 0x0430,
        AudioVideoCamcorder = 0x0434,
        AudioVideoVideoMonitor = 0x0438,
        AudioVideoVideoDisplayAndLoudspeaker = 0x043C,
        AudioVideoVideoConferencing = 0x0440,
        AudioVideoVideoGamingToy = 0x0448,

        // WEARABLE subType
        WearableUncategorized = 0x0700,
        WearableWristWatch = 0x0704,
        WearablePager = 0x0708,
        WearableJacket = 0x070C,
        WearableHelmet = 0x0710,
        WearableGlasses = 0x0714,

        // TOY subType
        ToyUncategorized = 0x0800,
        ToyRobot = 0x0804,
        ToyVehicle = 0x0808,
        ToyDollActionFigure = 0x080C,
        ToyController = 0x0810,
        ToyGame = 0x0814,

        // HEALTH subType
        HealthUncategorized = 0x0900,
        HealthBloodPressure = 0x0904,
        HealthThermometer = 0x0908,
        HealthWeighing = 0x090C,
        HealthGlucose = 0x0910,
        HealthPulseOximeter = 0x0914,
        HealthPulseRate = 0x0918,
        HealthDataDisplay = 0x091C,
    }
}