using JetBrains.Annotations;
using UnityEngine;

public class RobotLegScript : MonoBehaviour
{
    public float dir = 1.0f;
    public float maxRotation = 20.0f;
    public Rigidbody robot;
    public KeyCode startKey = KeyCode.Space;  // Define the key to start the robot
    public float backwardSpeed = 2.0f;  // Adjust the backward speed as needed

    private float _angle;
    private float _velocity = 35.0f;
    private bool _containsRobot;
    private bool _robotStarted;

    // Start is called before the first frame update
    void Start()
    {
        _containsRobot = robot != null;
        _robotStarted = false;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (Input.GetKeyDown(startKey))
        {
            _robotStarted = true;
        }

        if (!_robotStarted)
        {
            return;  // Do nothing if the robot hasn't started
        }

        var dt = Time.deltaTime;
        var deltaAngle = _velocity * dt * dir;
        if (Mathf.Abs(_angle + deltaAngle) > maxRotation)
        {
            _velocity *= -1.0f;
            deltaAngle *= -1.0f;
        }
        _angle += deltaAngle;

        if (_angle > 0)
        {
            transform.Rotate(Vector3.right, deltaAngle);
            if (!_containsRobot) return;
            var forwardMovement = -robot.transform.forward * (Mathf.Pow(_angle, 0.2f) * 1.5f * dt);
            robot.MovePosition(robot.position + forwardMovement);
        }
        else
        {
            // Move backward when the angle is negative
            transform.Rotate(Vector3.right, deltaAngle / 2);
            if (!_containsRobot) return;
            var backwardMovement = robot.transform.forward * backwardSpeed * dt;
            robot.MovePosition(robot.position + backwardMovement);
        }
    }
}
